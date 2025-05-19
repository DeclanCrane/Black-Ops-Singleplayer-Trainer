#include "D3D9Hook.h"

LPDIRECT3DDEVICE9 D3D9Hook::d3dDevice;
HWND D3D9Hook::hWnd;

D3D9Hook::_EndScene D3D9Hook::EndSceneCallback;
D3D9Hook::_Reset D3D9Hook::ResetCallback;

D3D9Hook::_EndScene D3D9Hook::pEndScene;
D3D9Hook::_Reset D3D9Hook::pReset;

HRESULT __stdcall D3D9Hook::EndSceneDetour(LPDIRECT3DDEVICE9 d3dDevice)
{
	// Save the application's Direct3D9 Device
	if (!D3D9Hook::d3dDevice)
		D3D9Hook::d3dDevice = d3dDevice;

	EndSceneCallback(d3dDevice);
	return pEndScene(d3dDevice);
}

HRESULT __stdcall D3D9Hook::ResetDetour(LPDIRECT3DDEVICE9 d3dDevice, D3DPRESENT_PARAMETERS* d3dpp)
{
	ResetCallback(d3dDevice, d3dpp);
	return pReset(d3dDevice, d3dpp);
}

D3D9Hook::D3D9Hook(_EndScene EndSceneCallback, _Reset ResetCallback, HWND hWnd)
	: EndScene(nullptr), Reset(nullptr), timeout(15)
{
	if(hWnd)
		D3D9Hook::hWnd = hWnd;
	D3D9Hook::EndSceneCallback = EndSceneCallback;
	D3D9Hook::ResetCallback = ResetCallback;
}

D3D9Hook::~D3D9Hook()
{
	// Do checks, might be already uninstalled when destructor is called
	Uninstall();
}

bool D3D9Hook::Install()
{
	IDirect3D9* pDirect3D9 = nullptr;
	D3DPRESENT_PARAMETERS d3dpp {};
	LPDIRECT3DDEVICE9 d3dDevice = nullptr;
	void** vmt = nullptr;

	pDirect3D9 = Direct3DCreate9(D3D_SDK_VERSION);
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	// Setup the dummy params
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = true;

	// Get the window handle if not passed in constructor
	if (!hWnd)
		hWnd = GetCurrentProcParentWindow();

	// Create a dummy D3D9 Device
	pDirect3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &d3dDevice);
	if (!d3dDevice) {
		pDirect3D9->Release();
		return false;
	}

	// Get the vtable of our dummy device
	vmt = *reinterpret_cast<void***>(d3dDevice);

	// Save the functions for later, need for resetting
	EndScene = vmt[42];
	Reset = vmt[16];

	// Create Detours
	pEndScene = (_EndScene)DetourFunction((PBYTE)EndScene, (PBYTE)EndSceneDetour);
	pReset = (_Reset)DetourFunction((PBYTE)Reset, (PBYTE)ResetDetour);

	if (!pEndScene || !pReset)
		return false;

	// Release the dummies
	d3dDevice->Release();
	pDirect3D9->Release();

	if (!WaitForUpdatedDevice())
		return false;

	return true;
}

bool D3D9Hook::Uninstall()
{
	DetourRemove((PBYTE)pEndScene, (PBYTE)EndSceneDetour);
	DetourRemove((PBYTE)pReset, (PBYTE)ResetDetour);
	return true;
}

bool D3D9Hook::Restore()
{
	// If we lose the window, we need to wait for
	// the application to create a new window
	auto start = std::chrono::steady_clock::now();
	while (true) {
		// Keep checking for updated window handle
		hWnd = GetCurrentProcParentWindow();

		// Make sure the handle is valid
		if (IsWindow(hWnd) && IsWindowEnabled(hWnd))
			break;

		// Check if we've waited too long
		if (std::chrono::steady_clock::now() - start > std::chrono::seconds(timeout))
			break;
	}

	if (!hWnd)
		return false;

	ResetHook();

	// Get a new device from EndScene
	d3dDevice = nullptr;
	WaitForUpdatedDevice();

	return true;
}

void D3D9Hook::ResetHook()
{
	Uninstall();

	pEndScene = (_EndScene)DetourFunction((PBYTE)EndScene, (PBYTE)EndSceneDetour);
	pReset = (_Reset)DetourFunction((PBYTE)Reset, (PBYTE)ResetDetour);
}

bool D3D9Hook::WaitForUpdatedDevice() const
{
	auto start = std::chrono::steady_clock::now();
	while (!d3dDevice) {
		if (d3dDevice)
			break;
		// Timeout
		if (std::chrono::steady_clock::now() - start > std::chrono::seconds(timeout))
			break;
	}

	if (d3dDevice)
		return true;
	return false;
}

bool D3D9Hook::HasWindowBeenLost()
{
	if (!IsWindow(D3D9Hook::hWnd))
		return true;
	return false;
}

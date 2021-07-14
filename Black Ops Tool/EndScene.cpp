#include "EndScene.h"


D3D9Hook::D3D9Hook()
{
	pDevice				= nullptr;
	pDirect3D9			= Direct3DCreate9(D3D_SDK_VERSION);
	d3dparams			= { 0 };
	vTable				= nullptr;
	EndSceneDetour		= nullptr;
	ResetDetour			= nullptr;
	pEndScene			= nullptr;
	pReset				= nullptr;
}

D3D9Hook::~D3D9Hook()
{
	// Prevents crash when ejecting
	CleanD3D9();
}


void D3D9Hook::SetupD3D9Params(HWND hWindow, BOOL isWindowed)
{
	d3dparams.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dparams.hDeviceWindow = hWindow;
	d3dparams.Windowed = isWindowed;
}

void D3D9Hook::CreateD3D9Device(HWND hWindow)
{
	pDirect3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dparams, &pDevice);

	if (!pDevice) {
		pDirect3D9->Release();
	}
}

void D3D9Hook::HookEndScene(HWND hWindow, endScene detourFunction, Reset resetFunction)
{
	SetupD3D9Params(hWindow, WindowFinder::CheckWindowMode(hWindow));
	CreateD3D9Device(hWindow);
	EndSceneDetour = detourFunction;
	ResetDetour = resetFunction;

	// Get the vTable
	vTable = *reinterpret_cast<void***>(pDevice);

	// Detour EndScene & Reset
	pEndScene = (endScene)DetourFunction((PBYTE)vTable[42], (PBYTE)EndSceneDetour);
	pReset = (Reset)DetourFunction((PBYTE)vTable[16], (PBYTE)ResetDetour);
}

void D3D9Hook::CleanD3D9()
{
	// Remove detours
	DetourRemove((PBYTE)pEndScene, (PBYTE)EndSceneDetour);
	DetourRemove((PBYTE)pReset, (PBYTE)ResetDetour);

	// Call reset after ejecting so some games don't crash
	pReset(pDevice, &d3dparams);

	pDevice->Release();
	pDirect3D9->Release();
}
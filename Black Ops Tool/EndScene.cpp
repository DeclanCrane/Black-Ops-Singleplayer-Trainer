#include "EndScene.h"

#include "../Include/detours.h"
#pragma comment(lib, "detours.lib")


D3D9Hook::D3D9Hook()
{
	pDevice = nullptr;
	pDirect3D9 = Direct3DCreate9(D3D_SDK_VERSION);
	d3dparams = { 0 };
	vTable = nullptr;
	Detour = nullptr;
	pEndScene = nullptr;

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

void D3D9Hook::HookEndScene()
{
	// Get the vTable
	vTable = *reinterpret_cast<void***>(pDevice);

	// Detour EndScene, index 42 in vTable is EndScene
	// Set pEndScene, to original function pointer
	pEndScene = (endScene)DetourFunction((PBYTE)vTable[42], (PBYTE)Detour);
}

void D3D9Hook::CleanD3D9()
{
	// Remove detour
	DetourRemove((PBYTE)pEndScene, (PBYTE)Detour);

	pDevice->Release();
	pDirect3D9->Release();
}
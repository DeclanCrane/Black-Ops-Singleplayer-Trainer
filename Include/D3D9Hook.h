#pragma once
#define D3D_DEBUG_INFO

#include <d3d9.h>
#include "NullSystem.h"
#include <chrono>
// Should replace with an undetected hooking method
#include "detours.h"
#pragma comment(lib, "detours.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

// Temp
#include <iostream>

class D3D9Hook {
	// The application's Direct3D9 Device
	static LPDIRECT3DDEVICE9 d3dDevice;
	static HWND hWnd;
	void* EndScene;
	void* Reset;
	// Time to wait for new windows and devices
	int timeout;

	typedef HRESULT(WINAPI* _EndScene)(LPDIRECT3DDEVICE9 d3dDevice);
	typedef HRESULT(WINAPI* _Reset)(LPDIRECT3DDEVICE9 d3dDevice, D3DPRESENT_PARAMETERS* d3dpp);

	// Detours
	static HRESULT WINAPI EndSceneDetour(LPDIRECT3DDEVICE9 d3dDevice);
	static HRESULT WINAPI ResetDetour(LPDIRECT3DDEVICE9 d3dDevice, D3DPRESENT_PARAMETERS* d3dpp);

	// Callbacks
	static _EndScene EndSceneCallback;
	static _Reset ResetCallback;

	// Trampolines
	static _EndScene pEndScene;
	static _Reset pReset;

public:
	// Optionally pass the window of the D3D9 application
	// If the hook fails try passing the window manually
	// [WARNING]: Manually passed windows do not support Restore functionality
	D3D9Hook(_EndScene EndSceneCallback, _Reset ResetCallback, HWND hWnd = nullptr);
	~D3D9Hook();
	bool Install();
	bool Uninstall();
	bool Restore();
	void ResetHook();
	inline LPDIRECT3DDEVICE9 GetDevice() const { return d3dDevice; }
	// Wait for EndScene to pass a new D3D device
	// Use SetTimeout to change wait time
	bool WaitForUpdatedDevice() const;
	// Returns current window of D3D9 hook
	inline HWND GetWindow() const { return hWnd;  }
	// Time in seconds to wait for new windows, and D3D devices
	inline int GetTimeout() const { return timeout;  }
	// Set the time to wait for new windows, and D3D devices
	inline int SetTimeout(int seconds) { timeout = seconds; }
	/*
		Some applcations will recreate the window instead of calling D3D9 reset
		when certain settings are changed (e.g. resolution).
		Older CoD games do this.
		Call this to make sure our window handle is still correct
	*/
	bool HasWindowBeenLost();
};
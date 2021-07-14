#pragma once

#include <Windows.h>
#include <tlhelp32.h>
#include <cstdio>
#include <tchar.h>
// Temp
#include <iostream>

namespace WindowFinder {

	BOOL CALLBACK EnumWindowsProc(
		_In_ HWND   hwnd,
		_In_ LPARAM lParam
	);

	struct handle_data {
		unsigned long process_id;
		HWND window_handle;
	};

	DWORD GetProcessIdByName(const WCHAR* processName);

	HWND GetWindowByProcessName(const WCHAR* processName);

	// Finds window by given window name
	HWND GetWindowByName(const char* windowName);

	// Checks if window is in fullscreen
	BOOL CheckWindowMode(HWND window);
}
#pragma once
#include <Windows.h>

struct Box
{
	int width, height;
};

struct WindowData
{
	int processID;
	HWND hWindow;
};

// Returns the passed monitor's size (resolution) in pixels
bool GetMonitorSize(HMONITOR hMonitor, Box &res);

// Returns the passed windows's size in pixels
bool GetWindowSize(HWND hWindow, Box &res);

// Returns true if function executed successfully
// bFullscreen returns true if window is fullscreen
bool IsWindowFullscreen(HWND hWindow, bool &bFullscreen);

// WARNING: This assumes application only has one window
// More than one window is undefined behavior
HWND GetCurrentProcessWindow();

// Get current processes' parent window
HWND GetCurrentProcParentWindow();

BOOL CALLBACK EnumWindowsForProcessID(HWND hWindow, LPARAM lParam);

BOOL CALLBACK EnumWindowsForProcParent(HWND hWnd, LPARAM lParam);
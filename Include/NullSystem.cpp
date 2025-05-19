#include "NullSystem.h"

bool GetMonitorSize(HMONITOR hMonitor, Box &res)
{
	MONITORINFO monInfo = {};

	// Get the monitor's information
	monInfo.cbSize = sizeof(MONITORINFO);

	if (!GetMonitorInfo(hMonitor, &monInfo))
		return false;

	// Calculate the monitors actual resolution
	res.width = monInfo.rcMonitor.right - monInfo.rcMonitor.left;
	res.height = monInfo.rcMonitor.bottom - monInfo.rcMonitor.top;

	return true;
}

bool GetWindowSize(HWND hWindow, Box &res)
{
	RECT rcWindow = {};

	// Get the window's coordinates
	if (!GetWindowRect(hWindow, &rcWindow))
		return false;

	// Calculate the window's actual size
	res.width = rcWindow.right - rcWindow.left;
	res.height = rcWindow.bottom - rcWindow.top;

	return true;
}

bool IsWindowFullscreen(HWND hWindow, bool &bFullscreen)
{
	HMONITOR hMonitor = NULL;
	Box monitorSize = {};
	Box windowSize = {};

	// Get the monitor that the window is active on
	// ( in-case there are more than one )
	hMonitor = MonitorFromWindow(hWindow, MONITOR_DEFAULTTONEAREST);
	if (!hMonitor)
		return false;

	// Get the monitor's resolution
	if (!GetMonitorSize(hMonitor, monitorSize))
		return false;

	// Get the target window's resolution
	if (!GetWindowSize(hWindow, windowSize))
		return false;

	if (monitorSize.width == windowSize.width && monitorSize.height == windowSize.height)
	{
		bFullscreen = true;
		return true;
	}

	bFullscreen = false;
	return true;
}

HWND GetCurrentProcessWindow()
{
	WindowData wd{};

	// Get our processes' current window
	wd.processID = GetCurrentProcessId();

	EnumWindows(&EnumWindowsForProcessID, (LPARAM)&wd);

	return wd.hWindow;
}

HWND GetCurrentProcParentWindow()
{
	WindowData wd{};

	// Get our processes' current window
	wd.processID = GetCurrentProcessId();

	EnumWindows(&EnumWindowsForProcParent, (LPARAM)&wd);

	return wd.hWindow;
}

BOOL CALLBACK EnumWindowsForProcParent(HWND hWnd, LPARAM lParam)
{
	DWORD procId = 0;
	char windowClassName[256] = "";

	GetWindowThreadProcessId(hWnd, &procId);

	if (procId != ((WindowData*)lParam)->processID)
		return TRUE;

	// Make sure it's enabled and visible
	if (!IsWindowVisible(hWnd) || !IsWindow(hWnd) || !IsWindowEnabled(hWnd))
		return TRUE;

	// We don't want to return any ConsoleWindowClass windows.
	// If you inject a DLL with a console window it'll grab that instead
	int windowTextLength = GetWindowTextLengthA(hWnd);
	GetClassNameA(hWnd, windowClassName, windowTextLength + 1);
	if (!strcmp(windowClassName, "ConsoleWindowClass"))
		return TRUE;

	// Make sure it's not a child window
	if (!GetParent(hWnd)) {
		((WindowData*)lParam)->hWindow = hWnd;
		return FALSE;
	}

	return TRUE; // Keep looking
}

BOOL CALLBACK EnumWindowsForProcessID(HWND hWindow, LPARAM lParam)
{
	// The process ID belonging to the current window
	DWORD currentWindowProcID = 0;
	char windowClassName[256] = "";

	GetWindowThreadProcessId(hWindow, &currentWindowProcID);

	// Get the HWNDs class information
	// to make sure it's not a console window
	int windowTextLength = GetWindowTextLengthA(hWindow);
	GetClassNameA(hWindow, windowClassName, windowTextLength + 1);

	// Make sure it's not a console window
	if (!strcmp(windowClassName, "ConsoleWindowClass"))
		return TRUE;

	// Make sure it's a window, enabled, and visible
	if (!IsWindowVisible(hWindow) || !IsWindow(hWindow) || !IsWindowEnabled(hWindow))
		return TRUE;

	if (currentWindowProcID == ((WindowData *)lParam)->processID
		&& !GetParent(hWindow))
	{
		((WindowData*)lParam)->hWindow = hWindow;
		return FALSE;
	}

	return TRUE; // Continue looking...
}

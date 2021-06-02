#include "WindowFinder.h"

HWND GetWindowByName(const char* windowName)
{
	HWND hWindow = FindWindowA(0, windowName);

	if (hWindow != NULL)
		return hWindow;

	else
		return nullptr;
}

BOOL CheckWindowMode(HWND window)
{
	// Structure containing window width and height
	RECT windowRect;

	// Gets the given window's width and height
	GetClientRect(window, &windowRect);

	/*
		Checks if the window's width and height are equal to the primary
		display's width and height. If they're equal the window must be
		fullscreen.
	*/
	if (windowRect.left			== 0 
		&& windowRect.top		== 0 
		&& windowRect.right		== GetSystemMetrics(SM_CXSCREEN) 
		&& windowRect.bottom	== GetSystemMetrics(SM_CYSCREEN))
	{
		// Window is Fullscreen
		return FALSE;
	}
	else
	{
		// Window is Windowed-Mode
		return TRUE;
	}
}
#pragma once

#include <Windows.h>

// TEMP used for debug logging
#include <iostream>

// Finds window by given window name
HWND GetWindowByName(const char* windowName);

// Checks if window is in fullscreen
BOOL CheckWindowMode(HWND window);
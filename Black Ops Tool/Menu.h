#pragma once

#include <Windows.h>

// DirectX9 Includes
#include <d3d9.h>
#include <d3dx9.h>

// ImGui Includes
#include "../Include/ImGUI/imgui.h"
#include "../Include/ImGUI/imgui_impl_dx9.h"
#include "../Include/ImGUI/imgui_impl_win32.h"

#include "Hack.h"
#include "Structs.h"
#include "Wall.h"

typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
// Original WndProc function
static WNDPROC oWndProc;

// For Menu Input
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

class ImGuiMenu
{
public:
	// If menu setup was complete
	bool bSetup;

	// If menu is to be shown
	bool bShowMenu;

	// If menu cursor is shown
	bool bShowCursor;

	// Window menu is drawn on
	HWND hWindow;

public:

	ImGuiMenu();
	~ImGuiMenu();

	// Setup for menu
	void SetupImGui(HWND hWindow, IDirect3DDevice9* pDevice);

	// Setup for menu input
	void SetupMenuInput(HWND hWindow);

	void CleanUp();

	// Where the menu is built
	void Menu();
};
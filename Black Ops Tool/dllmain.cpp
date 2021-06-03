// dllmain.cpp : Defines the entry point for the DLL application.
#include <Windows.h>

#include "Console.h"
#include "WindowFinder.h"
#include "EndScene.h"
#include "ImGuiMenuD3D9.h"

// Hack Headers
#include "Offsets.h"

// Handle to the DLL
static HMODULE DllHandle;

D3D9Hook BlackOpsHook;
ImGuiMenu BlackOpsMenu;

bool bConsole = false;

// Get the desired window
HWND hWindow = GetWindowByName("Call of Duty®: BlackOps");

// D3D9 EndScene Detour
HRESULT __stdcall EndSceneDetour(IDirect3DDevice9* pDevice)
{
    BlackOpsMenu.SetupImGui(hWindow, pDevice);
    BlackOpsMenu.Menu();

    // Call original endScene after detour
    return BlackOpsHook.pEndScene(pDevice);
}

DWORD __stdcall EjectThread(LPVOID lpParameter)
{
    Sleep(100);
    FreeLibraryAndExitThread(DllHandle, 0);
}

DWORD WINAPI MainThread(HINSTANCE hModule)
{

    // Create a console for printing
    Console console;
    console.PrintCustom("============================", ConsoleTextColor::darkBlue);
    console.PrintCustom("Black Ops Single Player Tool", ConsoleTextColor::lightBlue);
    console.PrintCustom("============================", ConsoleTextColor::darkBlue);
    console.PrintCustom("Creator: ShadyOrb", ConsoleTextColor::purple);

    //--------------------//
    // D3D9 EndScene Hook //
    //--------------------//
    BlackOpsHook.SetupD3D9Params(hWindow, CheckWindowMode(hWindow));
    BlackOpsHook.CreateD3D9Device(hWindow);
    BlackOpsHook.Detour = EndSceneDetour;
    BlackOpsHook.HookEndScene();

    // Main loop
    while (true)
    {
        // Eject Button
        if (GetAsyncKeyState(VK_END))
        {
            break;
        }

        if (GetAsyncKeyState(VK_DOWN) & 1)
        {
            if (bConsole)
            {
                *(int*)0x2910160 = 16;
                bConsole = false;
            }
        }

        if (GetAsyncKeyState(VK_UP) & 1)
        {
            if (!bConsole) {
                *(int*)0x2910160 = 17;
                bConsole = true;
            }
        }

        if (bInfiniteAmmoCheck)
        {
            std::cout << "It's true!\n";
            *(int*)primaryAmmoReserve   = 420;
            *(int*)secondaryAmmoReserve = 420;
            *(int*)tertiaryAmmoReserve  = 69;

            *(int*)grenadeAmmo      = 4;
            *(int*)equipmentAmmo    = 420;
        }
        if (bNoReloadCheck)
        {
            std::cout << "It's also true!\n";
            *(int*)primaryAmmoMag     = 69;
            *(int*)secondaryAmmoMag   = 69;
            *(int*)tertiaryAmmoMag    = 69;
        }

        // Show Menu
        if (GetAsyncKeyState(VK_INSERT) & 1)
        {
            if (!BlackOpsMenu.bShowMenu)
                BlackOpsMenu.bShowMenu = true;
            else
                BlackOpsMenu.bShowMenu = false;
        }
    }

    // Creates ejection thread
    CreateThread(NULL, 0, EjectThread, NULL, 0, NULL);

    return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        DllHandle = hModule;
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MainThread, NULL, 0, NULL);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

// dllmain.cpp : Defines the entry point for the DLL application.
#include <Windows.h>

#include "Console.h"
#include "EndScene.h"
#include "Menu.h"

#include "../Include/WindowFinder.h"
#pragma comment(lib, "WindowFinder.lib")

#include "Drawing.h"
#include "Entity.h"
#include "Hack.h"

// Handle to the DLL
static HMODULE DllHandle;

// Hook & Menu
D3D9Hook Hook;
ImGuiMenu Menu;

// Make sure D3D9 device is only passed once
static bool bGotDraw = false;

// Get the desired window
HWND hWindow = WindowFinder::GetWindowByProcessName(L"BlackOps.exe");

// D3D9 EndScene Detour
HRESULT __stdcall EndSceneDetour(IDirect3DDevice9* pDevice)
{
    // Pass the pDevice pointer to Drawing for drawing on screen
    if (!bGotDraw) {
        Drawing.pDevice = pDevice;
        bGotDraw = true;
    }

    // Menu
    Menu.SetupImGui(hWindow, pDevice);
    Menu.Menu();

    // Call Hack
    Hack::HackLoop();

    return Hook.pEndScene(pDevice);
}

HRESULT __stdcall ResetDetour(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters)
{
    return Hook.ResetDetour(pDevice, pPresentationParameters);
}

DWORD __stdcall EjectThread(LPVOID lpParameter)
{
    Sleep(100);
    FreeLibraryAndExitThread(DllHandle, 0);
    return 0;
}

DWORD WINAPI MainThread(HINSTANCE hModule)
{
    // Create a console for printing
    Console console;
    console.PrintCustom("=====================================", ConsoleTextColor::darkBlue);
    console.PrintCustom("    Black Ops Single Player Tool    ", ConsoleTextColor::lightBlue);
    console.PrintCustom("=====================================", ConsoleTextColor::darkBlue);
    console.PrintCustom("Creator: ShadyOrb", ConsoleTextColor::purple);

    //--------------------//
    // D3D9 EndScene Hook //
    //--------------------//
    Hook.HookEndScene(hWindow, EndSceneDetour, ResetDetour);

    // Main loop
    while (true)
    {
        // Eject Button
        if (GetAsyncKeyState(VK_END) & 1)
        {
            break;
        }

        // Toggle Menu
        if (GetAsyncKeyState(VK_INSERT) & 1)
        {
            Menu.bShowMenu = !Menu.bShowMenu;
        }

        // Toggle Developer Console
        if (GetAsyncKeyState(VK_DOWN) & 1)
        {
            Hack::ToggleConsole();
        } 

        // Teleport Zombies/Bots to Player
        if (GetAsyncKeyState(VK_F4) & 1) {
            Entity.TeleportEntities();
        }

        // Teleport Zombies/Bots and Aimbot
        if (GetAsyncKeyState(VK_F6) & 1) {
            Entity.TeleportEntities();
            Aimbot(Entity.cgEntities);
        }

        // Gives item selected in hack menu
        if (GetAsyncKeyState(VK_F5) & 1) {
            Hack::GiveItem(Hack::selectedItem);
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

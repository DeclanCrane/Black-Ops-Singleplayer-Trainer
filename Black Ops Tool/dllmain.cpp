// dllmain.cpp : Defines the entry point for the DLL application.
#include <Windows.h>

#include "Console.h"
#include "../Include/D3D9Hook.h"
#include "Menu.h"

#include "Drawing.h"
#include "Entity.h"
#include "Hack.h"

// Handle to the DLL
static HMODULE DllHandle;

// Hook & Menu
ImGuiMenu Menu;

// Make sure D3D9 device is only passed once
static bool bGotDraw = false;
static bool bMenuSetup = false;

HRESULT WINAPI EndSceneCallback(LPDIRECT3DDEVICE9 d3dDevice) {

    // Drawing Setup
    if (!bGotDraw) {
        Drawing.pDevice = d3dDevice;
        bGotDraw = true;
    }

    // Menu Setup
    if (Menu.bSetup) {
        Menu.Menu();
    }

    // Call Hack
    Hack::HackLoop();

    return 0;
}

HRESULT WINAPI ResetCallback(LPDIRECT3DDEVICE9 d3dDevice, D3DPRESENT_PARAMETERS* d3dpp) {
    std::cout << "Reset!\n";

    // Reset drawing device
    bGotDraw = false;

    // Reset ImGui
    Menu.CleanUp();
    bMenuSetup = false;

    return 0;
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
    D3D9Hook D3D9(EndSceneCallback, ResetCallback, GetCurrentProcessWindow());
    if (!D3D9.Install())
        std::cout << "Failure to capture D3D9\n";

    Menu.SetupImGui(GetCurrentProcParentWindow(), D3D9.GetDevice());

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

        // If application window is lost or reset
        if (D3D9.HasWindowBeenLost()) {
            Menu.CleanUp();
            D3D9.Restore();
            Menu.SetupImGui(D3D9.GetWindow(), D3D9.GetDevice());
        }

        if (GetAsyncKeyState(VK_F7) & 1) {
            std::string command = "give shrink_ray_zm";
            CBuf_AddText(0, command.c_str());
        }
    }

    Menu.CleanUp();
    D3D9.Uninstall();
    console.CloseConsole();

    // Creates ejection thread
    CreateThread(NULL, 0, EjectThread, NULL, 0, NULL);

    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule,
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

// dllmain.cpp : Defines the entry point for the DLL application.
#include <Windows.h>

#include "Console.h"
#include "WindowFinder.h"
#include "EndScene.h"
#include "Menu.h"

// Drawing
#include "Drawing.h"
#include "Entity.h"

#include "Hack.h"

#include "../Include/WindowFinder.h"
#pragma comment(lib, "WindowFinder.lib")

// Handle to the DLL
static HMODULE DllHandle;

D3D9Hook BlackOpsHook;
ImGuiMenu BlackOpsMenu;

bool bConsole = false;

typedef void(__cdecl* RenderScene_t)(int a1, int a2);
RenderScene_t RenderScene;

typedef void(__cdecl* GameFunc_t)();
GameFunc_t GameFunc;

static bool bGotDraw = false;

void myRenderScene(int a1, int a2)
{
    // DO STUFF

    RenderScene(a1, a2);
}

void myGameFunc()
{
    std::cout << "Hooked\n";
    GameFunc();
}

// Get the desired window
HWND hWindow = WindowFinder::GetWindowByProcessName(L"BlackOps.exe");

// D3D9 EndScene Detour
HRESULT __stdcall EndSceneDetour(IDirect3DDevice9* pDevice)
{
    // Pass the pDevice pointer to Drawing for drawing on screen
    if (!bGotDraw)
    {
        Drawing.pDevice = pDevice;
        bGotDraw = true;
    }

    
    // Menu Setup
    BlackOpsMenu.SetupImGui(hWindow, pDevice);
    BlackOpsMenu.Menu();

    // Call Hack
    Hack::HackLoop();

    return BlackOpsHook.pEndScene(pDevice);
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
    BlackOpsHook.SetupD3D9Params(hWindow, false);
    BlackOpsHook.CreateD3D9Device(hWindow);
    BlackOpsHook.Detour = EndSceneDetour;
    BlackOpsHook.HookEndScene();

    Bones.RegisterBones();

    //RenderScene = (RenderScene_t)DetourFunction((PBYTE)0x6C8CD0, (PBYTE)myRenderScene);
    //GameFunc = (GameFunc_t)DetourFunction((PBYTE)0x78F560, (PBYTE)myGameFunc);

    // Main loop
    while (true)
    {
        // Eject Button
        if (GetAsyncKeyState(VK_END) & 1)
        {
            break;
        }

        // Show Menu
        if (GetAsyncKeyState(VK_INSERT) & 1)
        {
            BlackOpsMenu.bShowMenu = !BlackOpsMenu.bShowMenu;
        }

        // Toggle Console
        if (GetAsyncKeyState(VK_DOWN) & 1)
        {
            bConsole = !bConsole;
            if(bConsole)
                *(int*)dwConsole = 16;
            if(!bConsole)
                *(int*)dwConsole = 17;
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

        if (GetAsyncKeyState(VK_F7) & 1) {
            BOOL bWindowed = WindowFinder::CheckWindowMode(hWindow);
            std::cout << bWindowed << "\n";
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

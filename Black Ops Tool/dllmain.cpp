// dllmain.cpp : Defines the entry point for the DLL application.
#include <Windows.h>

#include "Console.h"
#include "WindowFinder.h"
#include "EndScene.h"
#include "ImGuiMenuD3D9.h"

// Hack Headers
#include "Offsets.h"

// Drawing
#include "Drawing.h"
#include "Structs.h"
#include "Wall.h"

// For Drawing Text
#include <sstream>
#include <string.h>

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

    int nullIndex = 0; // The amount of null pointers in a row
    int enemyIndex = 0;
            // Temp
        DWORD enemyEntityList = 0x1BFBC84;
        while (nullIndex != 1) {
            DWORD currentEnemy = *(DWORD*)(enemyEntityList + (0x8C * enemyIndex));
            if (!currentEnemy) { // if currentEnemy is a nullptr
                nullIndex += 1;
            }
            else {
                vec2_t screen = { 0.f };
                //float entPosX, entPosY;
                vec3_t enemyWorldPos = { 0.f };
                int enemyMaxHealth = *(int*)(currentEnemy + 0x188);
                int enemyAliveCheck = *(int*)(currentEnemy + 0x164);
                if (enemyAliveCheck != 0) { // If enemy is alive

                    enemyWorldPos[0] = *(float*)(currentEnemy + 0x18); // Set enemy position vector
                    enemyWorldPos[1] = *(float*)(currentEnemy + 0x1C);
                    enemyWorldPos[2] = *(float*)(currentEnemy + 0x20);
                    vec3_t enemyHead3D;
                    enemyHead3D[0] = enemyWorldPos[0];
                    enemyHead3D[1] = enemyWorldPos[1];
                    enemyHead3D[2] = enemyWorldPos[2] + 65.f;
                    vec2_t enemyHead2D;

                    if (WorldToScreen(enemyWorldPos, screen)) { // Draw line if on screen
                        DrawLine(screen[0], screen[1], refdef->screenWidth / 2, refdef->screenHeight, 2, D3DCOLOR_ARGB(255, 0, 79, 82), pDevice);
                        if (WorldToScreen(enemyHead3D, enemyHead2D)) {
                            DrawEspBox2D(screen, enemyHead2D, 2, D3DCOLOR_ARGB(255,0,58,82), pDevice);
                        }
                    }
                    nullIndex = 0; // Reset nullIndex
                }
            }
            enemyIndex += 1;
        }

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

        if (GetAsyncKeyState(VK_LEFT) & 1) {
            Equipment->Grenades = 69;
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

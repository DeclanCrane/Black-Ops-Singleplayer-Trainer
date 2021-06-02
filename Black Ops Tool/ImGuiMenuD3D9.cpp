#include "ImGuiMenuD3D9.h"

#include "Offsets.h"

ImGuiMenu::ImGuiMenu()
{
    bSetup = false;
    bShowMenu = false;
    bShowCursor = false;
    hWindow = nullptr;
}

ImGuiMenu::~ImGuiMenu()
{
    CleanUp();
}

void ImGuiMenu::SetupImGui(HWND hWindow, IDirect3DDevice9* pDevice)
{
    // Setup ImGui
    if (!bSetup)
    {
        bSetup = true;

        // Stores window menu is drawn on
        this->hWindow = hWindow;

        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImGui::StyleColorsDark();
        ImGui_ImplWin32_Init(hWindow);
        ImGui_ImplDX9_Init(pDevice);

        // Shows mouse cursor
        ImGui::GetIO().MouseDrawCursor = true;

        // Sets up input for menu
        SetupMenuInput(hWindow);
    }
}

void ImGuiMenu::SetupMenuInput(HWND hWindow)
{
    // Sets up input hook
    oWndProc = (WNDPROC)SetWindowLongPtr(hWindow, GWL_WNDPROC, (LONG_PTR)WndProc);
}

void ImGuiMenu::CleanUp()
{
    // Removes input hook
    // Restore Original Input -- Fixes crash from ejecting
    (WNDPROC)SetWindowLongPtr(hWindow, GWL_WNDPROC, (LONG_PTR)oWndProc);
}

//-----------------------------NOTE-----------------------------------//
//  Turn this to a function pointer in the future...                  //
//  Or keeps as a demo window unless pointer is not equal to nullptr  //
//-----------------------------NOTE-----------------------------------//
void ImGuiMenu::Menu()
{
    if (bShowMenu)
    {
        ImGui::GetIO().MouseDrawCursor = true;

        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Black Ops Menu");

        ImGui::SliderFloat("Field of View", (float*)(*cg_fov + 0x18), 35.f, 120.f);
        ImGui::SliderFloat("FoV Scale", (float*)(*cg_fovScale + 0x18), 0.f, 2.5f);
        ImGui::SliderInt("FPS Cap", (int*)(*com_maxfps + 0x18), 5, 333);
        ImGui::Checkbox("Draw HUD", (bool*)(*cg_drawHud + 0x18));

        ImGui::Checkbox("Third Person", (bool*)(*cg_thirdPerson + 0x18));


        ImGui::Checkbox("Draw Gun", (bool*)(*cg_drawGun + 0x18));
        ImGui::SliderFloat("Gun X", (float*)(*cg_gun_x + 0x18), -20.f, 20.f);
        ImGui::SliderFloat("Gun Y", (float*)(*cg_gun_y + 0x18), -20.f, 20.f);
        ImGui::SliderFloat("Gun Z", (float*)(*cg_gun_z + 0x18), -20.f, 20.f);

        ImGui::InputInt("Zombies Credits", (int*)zombiesCredits);
        ImGui::Checkbox("Infinite Ammo", bInfiniteAmmoCheck);
        ImGui::Checkbox("No Reload",  bNoReloadCheck);

        ImGui::SliderFloat("Time Scale", (float*)(*timescale + 0x18), 0.f, 10.f);
        ImGui::SliderInt("Speed", (int*)(*g_speed + 0x18), 0, 1000);

        ImGui::End();

        ImGui::EndFrame();
        ImGui::Render();
        ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
    }
    else
    {
        ImGui::GetIO().MouseDrawCursor = false;
    }
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
        return true;

    return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}
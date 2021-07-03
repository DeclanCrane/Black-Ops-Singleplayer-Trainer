#include "Menu.h"

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
        // Disable mouse input in-game
        *(int*)dwMouseInput = 0;

        ImGui::GetIO().MouseDrawCursor = true;

        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Black Ops Menu");

        /* Toggles */
        ImGui::Text("Toggles");
        ImGui::Checkbox("Crosshair", &Hack::bDrawCrosshair);
        ImGui::Checkbox("Box ESP", &Hack::bDrawESPBox);
        ImGui::Checkbox("Line ESP", &Hack::bDrawESPLine);
        ImGui::Checkbox("Distance ESP", &Hack::bDrawDistanceESP);
        ImGui::Checkbox("Distance Alert", &Hack::bDrawDistanceAlert);
        //ImGui::Checkbox("Bone ESP", &Hack::bDrawESPBones);

        /* Crosshair Settings */
        ImGui::Text("Crosshair");
        ImGui::SliderFloat("Crosshair Gap", &Hack::crosshairGap, 0.f, 50.f, "%.1f", 1.f);
        ImGui::SliderFloat("Crosshair Length", &Hack::crosshairLength, 0.f, 50.f, "%.1f", 1.f);
        ImGui::SliderFloat("Crosshair Thickness", &Hack::crosshairThickness, 0.f, 50.f, "%.1f", 1.f);
        ImGui::ColorEdit3("Crosshair Color", &Hack::crosshairColor[0]);

        ImGui::Text("ESP Settings");
        ImGui::ColorEdit3("ESP Box Color", &Hack::ESPBoxColor[0]);
        ImGui::ColorEdit3("ESP Line Color", &Hack::ESPLineColor[0]);
        ImGui::ColorEdit3("ESP Distance Color", &Hack::ESPDistanceColor[0]);
        ImGui::ColorEdit3("Distance Alert Color", &Hack::distanceAlertColor[0]);

        ImGui::Text("Viewmodel");
        ImGui::SliderFloat("Gun X", (float*)&cg_gun_x->Value, -15.f, 15.f, "%.1f", 1.f);
        ImGui::SliderFloat("Gun Y", (float*)&cg_gun_y->Value, -15.f, 15.f, "%.1f", 1.f);
        ImGui::SliderFloat("Gun Z", (float*)&cg_gun_z->Value, -15.f, 15.f, "%.1f", 1.f); 
        ImGui::SliderFloat("FOV", (float*)&cg_fov->Value, 45.f, 240.f, "%.1f", 1.f);
        ImGui::SliderFloat("FOV Scale", (float*)&cg_fovScale->Value, 0.1, 2.f);

        ImGui::Text("Cheats");
        if (ImGui::Button("NoClip"))
            Hack::NoClip();

        if (ImGui::Button("God"))
            Hack::God();

        ImGui::Text("Stats");
        ImGui::InputText("Name", (char*)PlayerStats->PlayerName, 16);
        ImGui::InputInt("Credits", &PlayerStats->Points);
        ImGui::InputInt("Kills", &PlayerStats->Kills);
        ImGui::InputInt("Headshots", &PlayerStats->Headshots);

        ImGui::Text("Equipment");
        ImGui::InputInt("Primary Mag", &Equipment->PrimaryMagAmmo);
        ImGui::InputInt("Primary Reserve", &Equipment->PrimaryAmmoReserve);
        ImGui::InputInt("Secondary Mag", &Equipment->SecondaryMagAmmo);
        ImGui::InputInt("Secondary Reserve", &Equipment->SecondaryAmmoReserve);
        ImGui::InputInt("Tertiary Mag", &Equipment->TertiaryMagAmmo);
        ImGui::InputInt("Tertiary Reserve", &Equipment->TertiaryAmmoReserve);
        ImGui::InputInt("Grenades", &Equipment->Grenades);

        ImGui::Text("Settings");
        ImGui::SliderInt("FPS", &com_maxfps->Value, 0, 333);

        ImGui::Combo("Items", &Hack::selectedItem, itemNames);
        if (ImGui::Button("Give") & 1)
        {
            Hack::GiveItem(Hack::selectedItem);
        }

        ImGui::End();

        ImGui::EndFrame();
        ImGui::Render();
        ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
    }
    else
    {
        // Enable mouse input in-game
        *(int*)dwMouseInput = 1;

        ImGui::GetIO().MouseDrawCursor = false;
    }
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
        return true;

    return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}
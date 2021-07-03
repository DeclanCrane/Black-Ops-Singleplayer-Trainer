#pragma once

#include "Entity.h"
#include "Wall.h"
#include "Aimbot.h"
#include "Offsets.h"

#include "../Include/detours.h"
#include "../Include/ImGui/imgui.h"

class Hack
{
public:
    // Toggle Crosshair
    static bool bDrawCrosshair;
    static bool bCrosshairDisabled;
    static float crosshairThickness;
    static float crosshairGap;
    static float crosshairLength;
    static float crosshairColor[3];

    // Toggle Box ESP & Settings
    static bool bDrawESPBox;
    static bool bESPBoxRainbow;
    static float ESPBoxColor[3];

    // Toggle Line ESP & Settings
    static bool bDrawESPLine;
    static bool bESPLineRainbow;
    static float ESPLineColor[3];

    // Toggle Bone ESP
    static bool bDrawESPBones;

    static bool bDrawDistanceESP;
    static float ESPDistanceColor[3];

    static bool bDrawDistanceAlert;
    static float distanceAlertColor[3];

    // Item Selected in Menu
    static int selectedItem;

    // Used in RainbowESP
    static int colorIndex;

    //Constructor
    Hack();

    // Hack loop
    static void HackLoop();

    // Toggles noclip
    static void NoClip();

    // Toggles godmode
    static void God();

    // Gives player item at index
    static void GiveItem(int itemIndex);

    // Warns player if an enemy is too close
    static void EnemyDistanceAlert(entity_t* pEnt);

    // Rainbow ESP line and ESP box
    static void RainbowESP();

    static void DrawBoneESP(entity_t* pEnt);
};

/*

    Wrapper for ImGui menu to pass vectors

*/
namespace ImGui
{
    static auto vector_getter = [](void* vec, int idx, const char** out_text)
    {
        auto& vector = *static_cast<std::vector<std::string>*>(vec);
        if (idx < 0 || idx >= static_cast<int>(vector.size())) { return false; }
        *out_text = vector.at(idx).c_str();
        return true;
    };

    static bool Combo(const char* label, int* currIndex, std::vector<std::string>& values)
    {
        if (values.empty()) { return false; }
        return Combo(label, currIndex, vector_getter,
            static_cast<void*>(&values), values.size());
    }

    static bool ListBox(const char* label, int* currIndex, std::vector<std::string>& values)
    {
        if (values.empty()) { return false; }
        return ListBox(label, currIndex, vector_getter,
            static_cast<void*>(&values), values.size());
    }

}
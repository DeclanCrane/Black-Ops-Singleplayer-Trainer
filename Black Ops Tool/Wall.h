#pragma once

#include <string>
#include <math.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "../Include/ImGui/imgui.h"

#include "Structs.h"

#include "Drawing.h"
#include "Entity.h"
#include "Bones.h"

#include "Menu.h"

static float myColor[3];

bool WorldToScreen(vec3_t world, vec2_t &screen);

void Wall(entity_t* pEntity);

void DistanceESP(entity_t* pEnt);

void BoneESP(entity_t* pEnt, WORD wBone1, WORD wBone2);
#pragma once

#include "Structs.h"

#include "Drawing.h"
#include "Entity.h"

bool WorldToScreen(vec3_t world, vec2_t &screen);

void Wall(entity_t* pEntity);
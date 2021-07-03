#pragma once

#include "Math.h"

#include "Bones.h"
#include "Offsets.h"

#include <math.h>
#include <iostream>

#define MAX_FLOAT 10000000.f

int GetTarget(std::vector<entity_t*> &entityList);

void Aimbot(std::vector<entity_t*> &entityList);

bool IsVisible(vec3_t start, vec3_t end, int skipNumber);

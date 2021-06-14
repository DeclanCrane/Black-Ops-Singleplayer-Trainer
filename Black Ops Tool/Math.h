#pragma once

#include <math.h>
#include "Structs.h"

#define M_PI 3.14159265358979323846264338327950288

void GetAngleToTarget(vec3_t& vTargetPos, vec3_t& vCameraPos, vec3_t& vAngles);

void VectorAngles(const vec3_t& forward, vec3_t& angles);
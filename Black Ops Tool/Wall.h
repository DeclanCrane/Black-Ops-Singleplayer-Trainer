#pragma once

#include "Structs.h"

//DOESNT SEEM TO WORK
//bool WorldToScreen(vec3_t vWorldLocation, float Screen[2]);

bool WorldToScreen(vec3_t world, vec2_t &screen);

//bool WorldToScreen(vec3_t src, vec3_t dst, vec2_t& screen, float fovx, float fovy, float windowWidth, float windowHeight, vec3_t left, vec3_t up, vec3_t forward);
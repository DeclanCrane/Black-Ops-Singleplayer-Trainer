#pragma once

#include <Windows.h>

struct Vec2 {
	float x, y;
};

struct Vec3 {
	float x, y, z;
};

struct Vec4 {
	float x, y, z, w;
};

class Hack {
public:
	uintptr_t dwLocalEntity = 0x0;
	uintptr_t dwEntityList = 0x0;
	uintptr_t dwViewMatrix = 0x0;

	float viewMatrix[16];
};
#pragma once

#include <Windows.h>

// Offset to the value inside Dvar struct
// Ex. (*cg_fov + 0x18) = 65.0
#define oDvarValue 0x18

// =============
// Hack Settings
// =============
static bool* bInfiniteAmmoCheck;
static bool* bNoReloadCheck;


static uintptr_t zombiesCredits = (uintptr_t)(0x1C0A6C8);

static uintptr_t* cg_fov = (uintptr_t*)(0x02FF6888);
static uintptr_t* cg_fovScale = (uintptr_t*)(0x02FF66A8);
static uintptr_t * cg_drawGun = (uintptr_t*)(0x02F67F28);
static uintptr_t* cg_drawHud = (uintptr_t*)(0x02FF6714);


static uintptr_t* cg_thirdPerson = (uintptr_t*)(0x02F67B84);

static uintptr_t* cg_gun_x = (uintptr_t*)(0x02F67CC4);
static uintptr_t* cg_gun_y = (uintptr_t*)(0x02F67B30);
static uintptr_t* cg_gun_z = (uintptr_t*)(0x02F67C20);
static float* bAiming = (float*)(0x01C08CA8);

static uintptr_t* com_maxfps = (uintptr_t*)(0x02481760); 

static uintptr_t* g_speed = (uintptr_t*)(0x01C01810);
static uintptr_t* timescale = (uintptr_t*)(0x0248173C);

static uintptr_t primaryAmmoMag = (uintptr_t)(0x01C08F00);
static uintptr_t primaryAmmoReserve = (uintptr_t)(0x01C08E88);

static uintptr_t secondaryAmmoMag = (uintptr_t)(0x01C08F10);
static uintptr_t secondaryAmmoReserve = (uintptr_t)(0x01C08E98);

static uintptr_t tertiaryAmmoMag = (uintptr_t)(0x01C08AE8);
static uintptr_t tertiaryAmmoReserve = (uintptr_t)(0x01C08F20);

static uintptr_t equipmentAmmo = (uintptr_t)(0x01C08F18);
static uintptr_t grenadeAmmo = (uintptr_t)(0x01C08F18);



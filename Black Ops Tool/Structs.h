#pragma once

typedef float vec_t;
typedef float vec2_t[2];
typedef float vec3_t[3];

//struct Vector2 {
//	float x, y;
//};
//
//struct Vector3 {
//	float x, y, z;
//};

#define _USE_MATH_DEFINES

#define	PITCH					0
#define YAW						1
#define	ROLL					2

#define ANGLE2SHORT(x)          ((int)((x) * 65536 / 360) & 65535)
#define SHORT2ANGLE(x)          ((x)*(360.0 / 65536))

#define	VectorScale(v, s, o)	((o)[0]=(v)[0]*(s),(o)[1]=(v)[1]*(s),(o)[2]=(v)[2]*(s))
#define VectorCopy(a,b)			((b)[0]=(a)[0],(b)[1]=(a)[1],(b)[2]=(a)[2])

//ImGui copy
#define ImVec4Copy(i,v)	(v.x=i.x, v.y=i.y, v.z=i.z, v.w=i.w)

#define VectorSubtract(a,b,c)	((c)[0]=(a)[0]-(b)[0],(c)[1]=(a)[1]-(b)[1],(c)[2]=(a)[2]-(b)[2])
#define	VectorMA(v, s, b, o)	((o)[0]=(v)[0]+(b)[0]*(s),(o)[1]=(v)[1]+(b)[1]*(s),(o)[2]=(v)[2]+(b)[2]*(s))
#define DotProduct(x,y)			((x)[0]*(y)[0]+(x)[1]*(y)[1]+(x)[2]*(y)[2])


#define DegreesToRadians(a) ((a)*((float)M_PI/180.0f))
#define RadiansToDegrees(a) ((a)*(180.0f/(float)M_PI))
#define AngleNormalize(a) (SHORT2ANGLE(ANGLE2SHORT((a))))

#define ABS(x) ((x < 0) ? (-x) : (x))

class refdef_t
{
public:
	int x; //0x0000
	int y; //0x0004
	int screenWidth; //0x0008
	int screenHeight; //0x000C
	float fovX; //0x0010
	vec2_t fov; //0x0014
	char pad_001C[4]; //0x001C
	vec3_t eyePosition; //0x0020
	char pad_002C[8]; //0x002C
	vec3_t viewAxis[3]; //0x0034
	char pad_0064[12]; //0x0064
}; //Size: 0x0070
extern refdef_t* refdef;

class entity_t
{
public:
	char pad_0000[272]; //0x0000
	vec3_t HeadPos; //0x0110
	vec3_t WorldPos; //0x011C
	char pad_0128[4]; //0x0128
	float Rotation; //0x012C
	char pad_0130[52]; //0x0130
	bool isAlive; //0x0164
	char pad_0165[31]; //0x0165
	int Health; //0x0184
	int MaxHealth; //0x0188
	char pad_018C[112]; //0x018C
}; //Size: 0x01FC
extern entity_t* entity;

class localPlayer
{
public:
	int gameTime; //0x0000
	char pad_0004[8]; //0x0004
	bool bAiming; //0x000C
	char pad_000D[3]; //0x000D
	bool bAimingAtEnemy; //0x0010
	char pad_0011[3]; //0x0011
	int bState; //0x0014  /* 4 Normal | 5 GodMode | 6 Spectator */
	char pad_0018[12]; //0x0018
	vec3_t Origin; //0x0024
	vec3_t Velocity; //0x0030
	char pad_003C[88]; //0x003C
	bool bOnGround; //0x0094
	char pad_0095[211]; //0x0095
	float ADS; //0x0168
	char pad_016C[20]; //0x016C
	float Pitch; //0x0180
	float Yaw; //0x0184
	char pad_0188[8]; //0x0188
	float StancePosition; //0x0190
	char pad_0194[4]; //0x0194
	int Stance; //0x0198
}; //Size: 0x0490

class equipment_t //1C08E84
{
public:
	int PrimaryWeaponID; //0x0000
	int PrimaryAmmoReserve; //0x0004
	int PlayerID ; //0x0008 --UNSURE OF ADDRESS--
	char pad_000C[4]; //0x000C
	int SecondaryWeaponID; //0x0010
	int SecondaryAmmoReserve; //0x0014
	int TertiaryWeaponID; //0x0018
	int TertiaryAmmoReserve; //0x001C
	char pad_0020[88]; //0x0020
	int PrimaryWeaponID2; //0x0078
	int PrimaryMagAmmo; //0x007C
	int PlayerID2 ; //0x0080 --UNSURE OF ADDRESS--
	int Grenades; //0x0084
	int SecondaryWeaponID2; //0x0088
	int SecondaryMagAmmo; //0x008C
	int TertiaryWeaponID2; //0x0090
	int TertiaryMagAmmo; //0x0094
}; //Size: 0x00C0
extern equipment_t* Equipment;

class PlayerStats
{
public:
	char PlayerName[16]; //0x0000
	char pad_0004[64]; //0x0004
	int Points; //0x0050
	int Kills; //0x0054
	char pad_0058[28]; //0x0058
	int Headshots; //0x0074
}; //Size: 0x2A3C

typedef void* (__cdecl* MapRestart_t)(int i, int i2, const char * c);
extern MapRestart_t MapRestart;
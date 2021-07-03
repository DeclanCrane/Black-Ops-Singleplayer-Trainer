#pragma once

#include <Windows.h>
#include <vector>
#include <string>

typedef float vec_t;
typedef float vec2_t[2];
typedef float vec3_t[3];

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
enum entityType_t
{
	ET_GENERAL,
	ET_PLAYER,
	ET_PLAYER_CORPSE,
	ET_ITEM,
	ET_MISSILE,
	ET_INVISIBLE,
	ET_SCRIPTMOVER,
	ET_SOUND_BLEND,
	ET_FX,
	ET_LOOP_FX,
	ET_PRIMARY_LIGHT,
	ET_MG42,
	ET_HELICOPTER,
	ET_PLANE,
	ET_VEHICLE,
	ET_VEHICLE_COLLMAP,
	ET_VEHICLE_CORPSE,
	ET_ACTOR,
	ET_ACTOR_SPAWNER,
	ET_ACTOR_CORPSE,
	ET_STREAMER_HINT
};

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

class viewAngles_t //2911E20
{
public:
	float pitch;
	float yaw;
};
extern viewAngles_t* viewAngles;

class entity_t
{
public:
	int clientNum; //0x0000
	char pad_0000[256]; //0x0004
	vec3_t N000000F9; //0x0104
	vec3_t HeadPos; //0x0110
	vec3_t WorldPos; //0x011C
	char pad_0128[4]; //0x0128
	float Rotation; //0x012C
	char pad_0130[52]; //0x0130
	bool isAlive; //0x0164
	char pad_0165[31]; //0x0165
	int Health; //0x0184
	int MaxHealth; //0x0188
}; //Size: 0x018C
extern entity_t* entity;

class localPlayer_t
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
	vec3_t WorldPos; //0x0024
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
extern localPlayer_t* localPlayer;

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

class playerstats_t
{
public:
	char PlayerName[16]; //0x0000
	char pad_0004[64]; //0x0004
	int Points; //0x0050
	int Kills; //0x0054
	char pad_0058[28]; //0x0058
	int Headshots; //0x0074
}; //Size: 0x2A3C
extern playerstats_t* PlayerStats;

class dvar_t
{
public:
	char pad_0000[12]; //0x0000
	int MinValue; //0x000C
	int MaxValue; //0x0010
	char pad_0014[4]; //0x0014
	int Value; //0x0018
	char pad_001C[36]; //0x001C
}; //Size: 0x0040
extern dvar_t* cg_drawFPS;
extern dvar_t* com_maxfps;
extern dvar_t* cg_fov;
extern dvar_t* cg_fovScale;
extern dvar_t* g_timescale;
extern dvar_t* g_speed;
extern dvar_t* cg_drawCrosshair;
extern dvar_t* cg_gun_x;
extern dvar_t* cg_gun_y;
extern dvar_t* cg_gun_z;

enum TraceHitType
{
	TRACE_HITTYPE_NONE = 0,
	TRACE_HITTYPE_ENTITY = 1,
	TRACE_HITTYPE_DYNENT_MODEL = 2,
	TRACE_HITTYPE_DYNENT_BRUSH = 3,
	TRACE_HITTYPE_GLASS = 4,
};

struct trace_t
{
	/* 0x0000 */ vec3_t normal;
	/* 0x000C */ char unk1[0x04];
	/* 0x0010 */ float fraction;
	/* 0x0014 */ int sflags;
	/* 0x0018 */ int cflags;
	/* 0x001c */ enum TraceHitType hitType;
	/* 0x0020 */ unsigned short hitId;
	/* 0x0022 */ unsigned short modelIndex;
	/* 0x0024 */ unsigned short partName;
	/* 0x0026 */ unsigned short boneIndex;
	/* 0x0028 */ unsigned short partGroup;
	/* 0x002a */ bool allsolid;
	/* 0x002b */ bool startsolid;
	/* 0x002c */ bool walkable;
	/* 0x002d */ char Padding_455[3];
	/* 0x0030 */ struct cStaticModel_s* staticModel;
	/* 0x0034 */ int hitPartition;
};

static std::vector<std::string> itemNames = {
	"m16_zm", "gl_m16_upgraded_zm", "m16_gl_upgraded_zm", "g11_lps_zm", "g11_lps_upgraded_zm", "famas_zm", "famas_upgraded_zm",
	"ak74u_zm", "ak74u_upgraded_zm", "mp5k_zm", "mp5k_upgraded_zm", "mp40_zm", "mp40_upgraded_zm", "mpl_zm", "mpl_upgraded_zm",
	"pm63_zm", "pm63_upgraded_zm", "pm63lh_upgraded_zm", "spectre_zm", "spectre_upgraded_zm", "cz75dw_zm", "cz75lh_zm",
	"cz75dw_upgraded_zm", "cz75lh_upgraded_zm", "ithaca_zm", "ithaca_upgraded_zm", "rottweil72_zm", "rottweil72_upgraded_zm",
	"spas_zm", "spas_upgraded_zm", "hs10_zm", "hs10_upgraded_zm", "hs10lh_upgraded_zm", "aug_acog_zm", "aug_acog_mk_upgraded_zm",
	"mk_aug_upgraded_zm", "galil_zm", "galil_upgraded_zm", "commando_zm", "commando_upgraded_zm", "fnfal_zm", "fnfal_upgraded_zm",
	"dragunov_zm", "dragunov_upgraded_zm", "l96a1_zm", "l96a1_upgraded_zm", "rpk_zm", "rpk_upgraded_zm", "hk21_zm", "hk21_upgraded_zm",
	"m72_law_zm", "m72_law_upgraded_zm", "china_lake_zm", "china_lake_upgraded_zm", "zombie_cymbal_monkey", "freezegun_zm", "ray_gun_zm",
	"crossbow_explosive_upgraded_zm", "bowie_knife_zm", "knife_ballistic_zm", "knife_ballistic_upgraded_zm", "knife_ballistic_bowie_zm",
	"knife_ballistic_bowie_upgraded_zm", "explosive_bolt_zm", "explosive_bolt_upgraded_zm", "syrette_sp", "zombie_perk_bottle_doubletap",
	"zombie_perk_bottle_jugg"
};

enum items {
	M16, M16_GL, M16_GL_Upgraded, G11, G11_Upgraded, Famas, Famas_Upgraded,
	AK74u, AK74u_Upgraded, MP5K, MP5K_Upgraded, MP40, MP40_Upgraded, MPL, MPL_Upgraded,
	PM63, PM63_Upgraded, PM63_DualWield, Spectre, Spectre_Upgraded, CZ75_DualWield, CZ75_DualWield_OneHand,
	CZ75_DualWield_Upgraded, CZ75_DualWield_OneHand_Upgraded, Stakeout, Stakeout_Upgraded, Olympia, Olympia_Upgraded,
	Spas12, Spas12_Upgraded, HS10, HS10_Upgraded, HS10_OneHand_Upgraded, AUG, AUG_MK_Upgraded,
	AUG_Upgraded, Galil, Galil_Upgraded, Commando, Commando_Upgraded, FNFAL, FNFAL_Upgraded,
	Dragonov, Dragonov_Upgraded, L96A1, L96A1_Upgraded, RPK, RPK_Upgraded, HK21, HK21_Upgraded,
	M72_LAW, M72_LAW_Upgraded, ChinaLake, ChinaLake_Upgraded, Zombie_Cymbal_Monkey, FreezeGun, RayGun,
	Crossbow_Upgraded, BowieKnife, BallisticKnife, BallisticKnife_Upgraded, Ballistic_Bowie,
	Ballistic_Bowie_Upgraded, Explosive_Bolt, Explosive_Bolt_Upgraded, Syrette, DoubleTap_Bottle, Juggernaut_Bottle
};
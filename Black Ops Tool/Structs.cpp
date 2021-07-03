#include "Structs.h"

refdef_t*		refdef				= (refdef_t*)0x29CF5530;
viewAngles_t*	viewAngles			= (viewAngles_t*)0x2911E20;

localPlayer_t*	localPlayer			= (localPlayer_t*)0x1C08B40;

equipment_t*	Equipment			= (equipment_t*)0x1C08E84;
playerstats_t*	PlayerStats			= (playerstats_t*)0x1C0A678;

dvar_t*	cg_drawFPS			= *(dvar_t**)0x2F67B68;
dvar_t*	com_maxfps			= *(dvar_t**)0x2481760;

dvar_t* cg_fov				= *(dvar_t**)0x2FF6888;
dvar_t* cg_fovScale			= *(dvar_t**)0x2FF66A8;
dvar_t* cg_drawGun			= *(dvar_t**)0x2F67F28;
dvar_t* cg_drawHud			= *(dvar_t**)0x2FF6714;
dvar_t* cg_drawCrosshair	= *(dvar_t**)0x2F67BC4;

dvar_t* cg_thirdPerson		= *(dvar_t**)0x2F67B84;

dvar_t* cg_gun_x			= *(dvar_t**)0x2F67CC4;
dvar_t* cg_gun_y			= *(dvar_t**)0x2F67B30;
dvar_t* cg_gun_z			= *(dvar_t**)0x2F67C20;

dvar_t* g_speed				= *(dvar_t**)0x1C01810;
dvar_t* g_timescale			= *(dvar_t**)0x248173C;
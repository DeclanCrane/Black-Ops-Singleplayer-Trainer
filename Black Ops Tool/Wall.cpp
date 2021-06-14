#include "Wall.h"
#include <math.h>

//SAMPLE WORLD TO SCREEN
bool WorldToScreen(vec3_t world, vec2_t& screen)
{
	vec3_t Position;
	VectorSubtract(world, refdef->eyePosition, Position);
	vec3_t Transform;

	// get our dot products from viewAxis
	Transform[0] = DotProduct(Position, refdef->viewAxis[1]);
	Transform[1] = DotProduct(Position, refdef->viewAxis[2]);
	Transform[2] = DotProduct(Position, refdef->viewAxis[0]);


	// make sure it is in front of us
	if (Transform[2] < 0.1f)
		return false;

	// get the center of the screen
	//vec2_t Center = vec2_t((float)RefDef->scrWidth * 0.5f, (float)RefDef->scrHeight * 0.5f);
	vec2_t CenterScreen;
	CenterScreen[0] = refdef->screenWidth / 2;
	CenterScreen[1] = refdef->screenHeight / 2;

	screen[0] = CenterScreen[0] * (1 - (Transform[0] / refdef->fovX / Transform[2]));
	screen[1] = CenterScreen[1] * (1 - (Transform[1] / refdef->fov[0] / Transform[2]));
	return true;
}

void Wall(entity_t* pEntity)
{
    vec2_t screen = { 0.f };
    vec3_t enemyWorldPos = { 0.f };
	if (pEntity->isAlive) { // If enemy is alive
		vec3_t enemyHead3D;
		vec2_t enemyHead2D;
		if (WorldToScreen(pEntity->WorldPos, screen)) {
			// Line ESP
			//DrawLine(screen[0], screen[1], refdef->screenWidth / 2, refdef->screenHeight, 2, D3DCOLOR_ARGB(255, 0, 79, 82), pDevice); Fix pDevice

			// Box ESP
			if (WorldToScreen(enemyHead3D, enemyHead2D)) {
				//DrawEspBox2D(screen, enemyHead2D, 2, D3DCOLOR_ARGB(255, 0, 58, 82), pDevice); Fix pDevice
			}
		}
	}
}

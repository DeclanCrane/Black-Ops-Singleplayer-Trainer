#include "Wall.h"

//SAMPLE WORLD TO SCREEN
bool WorldToScreen(vec3_t world, vec2_t& screen)
{
	vec3_t Position;
	VectorSubtract(world, refdef->eyePosition, Position);
	vec3_t Transform;

	// Get our dot products from viewAxis
	Transform[0] = DotProduct(Position, refdef->viewAxis[1]);
	Transform[1] = DotProduct(Position, refdef->viewAxis[2]);
	Transform[2] = DotProduct(Position, refdef->viewAxis[0]);


	// Make sure it is in front of us
	if (Transform[2] < 0.01f)
		return false;

	// Get the center of the screen
	vec2_t CenterScreen;
	CenterScreen[0] = refdef->screenWidth / 2;
	CenterScreen[1] = refdef->screenHeight / 2;

	screen[0] = CenterScreen[0] * (1 - (Transform[0] / refdef->fovX / Transform[2]));
	screen[1] = CenterScreen[1] * (1 - (Transform[1] / refdef->fov[0] / Transform[2]));
	return true;
}

void Wall(entity_t* pEntity)
{
	if (pEntity->isAlive) { // If enemy is alive

		vec2_t enemyScreenPos = { 0.f };
		vec2_t enemyHead2D = { 0.f };

		if (WorldToScreen(pEntity->WorldPos, enemyScreenPos)) {

			// Line ESP
			if (Hack::bDrawESPLine)
			{
				Drawing.DrawLine(enemyScreenPos[0], enemyScreenPos[1], refdef->screenWidth / 2, refdef->screenHeight, 1,
					D3DCOLOR_ARGB(255, int(Hack::ESPLineColor[0] * 255), int(Hack::ESPLineColor[1] * 255), int(Hack::ESPLineColor[2] * 255)));
			}

			// Top of box
			vec3_t vHeadOrigin = { 0.f };
			vHeadOrigin[0] = pEntity->WorldPos[0];
			vHeadOrigin[1] = pEntity->WorldPos[1];
			vHeadOrigin[2] = pEntity->WorldPos[2] + 65.f; // Height of Zombie / Bot

			// Box ESP
			if (Hack::bDrawESPBox)
			{
				if (WorldToScreen(vHeadOrigin, enemyHead2D)) {
					Drawing.DrawEspBox2D(enemyScreenPos, enemyHead2D, 1, D3DCOLOR_ARGB(255, int(Hack::ESPBoxColor[0] * 255), int(Hack::ESPBoxColor[1] * 255), int(Hack::ESPBoxColor[2] * 255)));
				}
			}
		}
	}
}

void DistanceESP(entity_t* pEnt)
{
	vec3_t vEnemyOrigin = { pEnt->WorldPos[0], pEnt->WorldPos[1], pEnt->WorldPos[2] };

	vec2_t vFontScreenPos;
	if(WorldToScreen(vEnemyOrigin, vFontScreenPos))
	{
		// Gets the distance from the enemy						// This needs to be cleaned up.
		float distanceFromEnemy = sqrtf(localPlayer->WorldPos[0] - vEnemyOrigin[0] * (localPlayer->WorldPos[0] - vEnemyOrigin[0])
			+ (localPlayer->WorldPos[1] - vEnemyOrigin[1]) * (localPlayer->WorldPos[1] - vEnemyOrigin[1])
			+ (localPlayer->WorldPos[2] - vEnemyOrigin[2]) * (localPlayer->WorldPos[2] - vEnemyOrigin[2]));

		// Convert CM to M
		distanceFromEnemy = distanceFromEnemy / 100;

		// Format the string
		std::string text = std::to_string(distanceFromEnemy);
		text.resize(3);

		// If the last character is '.', remove it.
		if (text.back() == (char)".") {
			text.pop_back();
		}

		text.append(" M");

		Drawing.DrawFont(text.c_str(), vFontScreenPos[0], vFontScreenPos[1], 
			D3DCOLOR_ARGB(255, int(Hack::ESPDistanceColor[0] * 255), int(Hack::ESPDistanceColor[1] * 255), int(Hack::ESPDistanceColor[2] * 255)));
	}
}

void BoneESP(entity_t* pEnt, WORD wBone1, WORD wBone2)
{
	// World coords
	vec3_t vBone1Pos = { 0.f };
	vec3_t vBone2Pos = { 0.f };

	// Screen coords
	vec2_t vBone1Screen = { 0.f };
	vec2_t vBone2Screen = { 0.f };

	if (Bones.GetBoneVector(pEnt, wBone1, vBone1Pos) && Bones.GetBoneVector(pEnt, wBone2, vBone2Pos))
	{
		if (WorldToScreen(vBone1Pos, vBone1Screen) && WorldToScreen(vBone2Pos, vBone2Screen))
		{
			Drawing.DrawLine(vBone1Screen, vBone2Screen, 1.f, D3DCOLOR_ARGB(255, 255, 0, 0));
		}
	}
}

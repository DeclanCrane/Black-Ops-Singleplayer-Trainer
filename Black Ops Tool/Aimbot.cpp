#include "Aimbot.h"

int GetTarget(std::vector<entity_t*> &entityList)
{
	int bestTarget = -1;
	float closestEntity = MAX_FLOAT;
	int entityListSize = entityList.size();

	for (int i = 0; i < entityListSize; i++)
	{
		if (entityList[i]->isAlive)
		{
			// Gets the distance from the enemy						// This needs to be cleaned up.
			float distanceFromEnemy = sqrtf(localPlayer->WorldPos[0] - entityList[i]->WorldPos[0] * (localPlayer->WorldPos[0] - entityList[i]->WorldPos[0])
										+ (localPlayer->WorldPos[1] - entityList[i]->WorldPos[1]) * (localPlayer->WorldPos[1] - entityList[i]->WorldPos[1])
										+ (localPlayer->WorldPos[2] - entityList[i]->WorldPos[2]) * (localPlayer->WorldPos[2] - entityList[i]->WorldPos[2]));

			// Check if it is the cloest entity
			if (distanceFromEnemy < closestEntity)
			{
				closestEntity = distanceFromEnemy;
				bestTarget = i;
			}
		}
	}
	// If there's no good target (They're all dead)
	if (bestTarget == -1)
		return -1;
	else
		return bestTarget; // Return best target
}

void Aimbot(std::vector<entity_t*> &entityList)
{
	// Get the aimbot target
	int pTarget = GetTarget(entityList);

	// If there is no valid target
	if (pTarget == -1)
		return;

	// Gets the distance from the enemy						// This needs to be cleaned up.
	float distanceFromEnemy = sqrtf(localPlayer->WorldPos[0] - entityList[pTarget]->WorldPos[0] * (localPlayer->WorldPos[0] - entityList[pTarget]->WorldPos[0])
								+ (localPlayer->WorldPos[1] - entityList[pTarget]->WorldPos[1]) * (localPlayer->WorldPos[1] - entityList[pTarget]->WorldPos[1])
								+ (localPlayer->WorldPos[2] - entityList[pTarget]->WorldPos[2]) * (localPlayer->WorldPos[2] - entityList[pTarget]->WorldPos[2]));

	//[REMOVED CRASHES THE GAME(W.I.P)]
	// Get the bone to aim at			
	//vec3_t bonePosition = { 0.f };
	//Bones.GetEntityBones(entityList[pTarget], Bones.bones[j_helmet], bonePosition);

	// Prevents laggy mouse movement and game crashing from large viewAngle floats
	if (viewAngles->pitch > 9000.f || viewAngles->yaw > 9000.f) {
		viewAngles->pitch = 0.f;
		viewAngles->yaw = 0.f;
	}

	// This is temporary, aims at upper-chest. Should be replaced with getting a bone position
	vec3_t aimPosition = {entityList[pTarget]->WorldPos[0], entityList[pTarget]->WorldPos[1], entityList[pTarget]->WorldPos[2] + 55.f };

	// Get angles to target
	vec3_t aimbotAngles;
	GetAngleToTarget(aimPosition, refdef->eyePosition, aimbotAngles);

	// Get the delta
	vec2_t delta;
	delta[0] = aimbotAngles[0] - localPlayer->Yaw; // X
	delta[1] = aimbotAngles[1] - localPlayer->Pitch; // Y

	// Add the delta to our player's view position
	viewAngles->yaw += delta[0];
	viewAngles->pitch += delta[1];
}

bool IsVisible(vec3_t start, vec3_t end, int skipNumber)
{
	trace_t tr;
	// OLD MASK 0x803003
	CGTrace(&tr, start, end, skipNumber, 0x803003, 0, 0);

	return (tr.fraction != 1.0f);
}

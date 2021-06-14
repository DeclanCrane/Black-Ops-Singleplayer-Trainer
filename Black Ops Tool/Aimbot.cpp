#include "Aimbot.h"

int GetTarget()
{
	int bestTarget = -1;
	float min = INT_MAX;
	for (int i = 0; i < 5; i++)
	{
		DWORD enemyEntityList = 0x1BFBC84;

		DWORD currentEnemy = *(DWORD*)(enemyEntityList + (0x8C * i));

		// If enemy isn't alive or the pointer is null
		int enemyAliveCheck = *(int*)(currentEnemy + 0x164);
		if (enemyAliveCheck == 0 || currentEnemy == NULL)
		{
			std::cout << "Failed at alive\n";
			continue;
		}
		else
		{
			vec3_t enemyPosition = { 0.f };
			enemyPosition[0] = *(float*)(currentEnemy + 0x18); // Set enemy position vector
			enemyPosition[1] = *(float*)(currentEnemy + 0x1C);
			enemyPosition[2] = *(float*)(currentEnemy + 0x20);
			//enemyPosition[2] += 55.f;
			if (enemyPosition[0] == 0.f && enemyPosition[1] == 0.f && enemyPosition[2] == 0.f) {
				std::cout << "No position\n";
				continue;
			}

			float distanceFromEnemy = 0.f;
			distanceFromEnemy = sqrtf((enemyPosition[0] - localPlayer->Origin[0]) * (enemyPosition[0] - localPlayer->Origin[0]) + (enemyPosition[1] - localPlayer->Origin[1]) * (enemyPosition[1] - localPlayer->Origin[1]) + (enemyPosition[2] - localPlayer->Origin[2]) * (enemyPosition[2] - localPlayer->Origin[2]));

			if (distanceFromEnemy == 0.f) {
				std::cout << "No distance\n";
			}

			if (distanceFromEnemy < min)
			{
				min = distanceFromEnemy;
				bestTarget = i;
			}
		}
	}
	return bestTarget;
}

void Aimbot()
{
	int target = GetTarget();
	if (target == -1) {
		std::cout << "NO TARGET\n";
	}

	DWORD enemyEntityList = 0x1BFBC84;

	DWORD currentEnemy = *(DWORD*)(enemyEntityList + (0x8C * target));
	if (currentEnemy == NULL) {
		return;
	}

	vec3_t enemyPosition = { 0.f };
	enemyPosition[0] = *(float*)(currentEnemy + 0x18); // Set enemy position vector
	enemyPosition[1] = *(float*)(currentEnemy + 0x1C);
	enemyPosition[2] = *(float*)(currentEnemy + 0x20);
	enemyPosition[2] += *(float*)(currentEnemy + 0x118);
	std::cout << "enemyPosition X:" << enemyPosition[0] << "\nenemyPosition Y:" << enemyPosition[1] << "\nenemyPosition Z:" << enemyPosition[2] << std::endl;

	float distanceFromEnemy = 0.f;
	distanceFromEnemy = sqrtf((enemyPosition[0] - localPlayer->Origin[0]) * (enemyPosition[0] - localPlayer->Origin[0]) + (enemyPosition[1] - localPlayer->Origin[1]) * (enemyPosition[1] - localPlayer->Origin[1]) + (enemyPosition[2] - localPlayer->Origin[2]) * (enemyPosition[2] - localPlayer->Origin[2]));

	vec3_t aimbotAngles = { 0.f };
	GetAngleToTarget(enemyPosition, refdef->eyePosition, aimbotAngles);

	std::cout << "AimbotAngles X:" << aimbotAngles[0] << "\AimbotAngles Y:" << aimbotAngles[1] << std::endl;

	vec2_t Delta = { 0.f };
	Delta[0] = aimbotAngles[0] - localPlayer->Yaw; // X
	Delta[1] = aimbotAngles[1] - localPlayer->Pitch; // Y

	std::cout << "Delta X:" << Delta[0] << "\nDelta Y:" << Delta[1] << std::endl;

	viewAngles->yaw		+= Delta[0];
	viewAngles->pitch	+= Delta[1];
}

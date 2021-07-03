#include "Entity.h"

Entity_t Entity;

bool Entity_t::GetEntities()
{
	cgEntities.clear();

	for (int i = 0; i < MAX_ENTS; i++)
	{
		DWORD * pEntityBuffer = (DWORD*)*(DWORD*)(dwEntityList + (0x8C * i));

		// If it's a valid entity pointer
		if (pEntityBuffer != nullptr)
		{
			entity_t* pEnt = (entity_t*)pEntityBuffer;
			// Extra check to make sure it's an entity
			if (pEnt->MaxHealth > 100 && pEnt->MaxHealth < 1500)
			{
				cgEntities.push_back((entity_t*)pEntityBuffer);
			}
		}
	}

	return true;
}

void Entity_t::TeleportEntities()
{
	// Get the player's origin
	vec3_t vPlayerOrigin = { localPlayer->WorldPos[0], 
							 localPlayer->WorldPos[1],
							 localPlayer->WorldPos[2] };

	// Add distance from player
	vPlayerOrigin[0] += 200.f;

	// For each entity
	for (int i = 0; i < cgEntities.size(); i++)
	{
		cgEntities[i]->WorldPos[0] = vPlayerOrigin[0];
		cgEntities[i]->WorldPos[1] = vPlayerOrigin[1];
		cgEntities[i]->WorldPos[2] = vPlayerOrigin[2];
	}
}

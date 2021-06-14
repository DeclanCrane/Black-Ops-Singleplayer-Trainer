#include "Entity.h"

Entity_t Entity;

void Entity_t::GetEntities()
{
	cgEntities.clear();

	for (int i = 0; i < MAX_ENTS; i++)
	{
		DWORD * pEntityBuffer = (DWORD*)*(DWORD*)(dwEntityList + (0x8C * i));
		if (pEntityBuffer != nullptr)
		{
			cgEntities.push_back((entity_t*)pEntityBuffer);
		}
	}
}

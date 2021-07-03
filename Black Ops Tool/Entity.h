#pragma once

#include <Windows.h>
#include <vector>
#include <iostream>

#include "Structs.h"
#include "Offsets.h"

#define MAX_ENTS 32 // I DON'T KNOW MAX ENTS, NEEDS TESTING



class Entity_t {
public:
	// Stores all the entities
	std::vector<entity_t*> cgEntities;

public:
	// Sorts entities and stores them
	bool GetEntities();

	void TeleportEntities();
};
extern Entity_t Entity;
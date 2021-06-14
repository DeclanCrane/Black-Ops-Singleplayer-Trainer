#pragma once

#include <Windows.h>
#include <vector>
#include <iostream>

#include "Structs.h"
#include "Offsets.h"

#define MAX_ENTS 24 // I DON'T KNOW MAX ENTS, NEEDS TESTING



class Entity_t {
public:
	std::vector<entity_t*> cgEntities;

public:
	void GetEntities();
};
extern Entity_t Entity;
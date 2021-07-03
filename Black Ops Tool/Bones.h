#pragma once

#include <iostream>
#include <vector>

#include "Structs.h"
#include "Offsets.h"

// Enums of bones for accessing bones vector
enum TAGS
{
	/*Head*/  j_helmet, j_head, j_neck
	/*Arms*/, j_shoulder_le, j_shoulder_ri, j_elbow_le, j_elbow_ri, j_wrist_le, j_wrist_ri
	/*Back*/, j_mainroot, j_spineupper, j_spinelower, j_spine4
	/*Legs*/, j_hip_ri, j_hip_le, j_knee_le, j_knee_ri, j_ankle_ri, j_ankle_le, NUM_TAGS
};


class Bones_t {
public:
	// Names of bones
	std::vector<std::string> tagNames = {

		/*Head*/          "j_helmet"     , "j_head"         , "j_neck"
		/*Arms*/        , "j_shoulder_le", "j_shoulder_ri"  , "j_elbow_le"   , "j_elbow_ri", "j_wrist_le", "j_wrist_ri"
		/*Back*/        , "j_mainroot"   , "j_spineupper"   , "j_spinelower" , "j_spine4"
		/*Legs*/        , "j_hip_ri"     , "j_hip_le"       , "j_knee_le"    , "j_knee_ri" , "j_ankle_ri", "j_ankle_le"
	};

	// Stores the registered bone IDs
	std::vector<WORD> bones;

	// Gets the in-game bone IDs
	void RegisterBones();
	// Gets bone position from zombies or bots
	bool GetEntityBones(entity_t* pEnt, WORD wBone, vec3_t vOrigin);

	// Gets bone position from zombies or bots
	bool GetEntityBones();

	// Gets bone position from real players
	void GetPlayerBones(DWORD pEnt, WORD wBone, vec3_t vOrigin);

	// Temp for testing
	bool GetTagPosition(short tag, entity_t* pEnt, float* vec);

	// Get bone position
	bool GetBoneVector(entity_t* pEnt, short tag, vec3_t &vOrigin);
};

extern Bones_t Bones;
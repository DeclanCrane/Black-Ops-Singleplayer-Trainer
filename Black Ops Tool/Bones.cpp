#include "Bones.h"

Bones_t Bones;

// Gets the in-game bone IDs
void Bones_t::RegisterBones()
{
	bones.clear();

	for (int i = 0; i < NUM_TAGS; i++)
	{
		WORD bone = (WORD) RegisterTag(tagNames[i].c_str(), 0);
		bones.push_back(bone);
	}
}

// Gets bone position from zombies or bots
bool Bones_t::GetEntityBones(entity_t* pEnt, WORD wBone, vec3_t vOrigin)
{
	if (!wBone) // If bone is invalid
		return false;

	void* result = GetBoneInfo(pEnt->clientNum, 0); // Gets BoneInfo from entity's client number
	if (result)
	{
		if (GetTagPos(pEnt, result, wBone, vOrigin)) // Gets the bone's world position
			return true;
	}

	return false;
}

bool Bones_t::GetBoneVector(entity_t* pEnt, short tag, vec3_t &vOrigin)
{
	if (pEnt)
	{
		// Get the entity's mesh
		void* mesh = GetBoneInfo(pEnt->clientNum, 0);
		if (!mesh)
			return false;

		// Get the address of the tag pos
		int vOriginAddress = CG_ReturnTagPos((int)pEnt, mesh, tag);
		if (vOriginAddress == 0)
			return false;

		// Get the tag position vector
		vOrigin[0] = *(float*)(vOriginAddress + 0x10);
		vOrigin[1] = *(float*)(vOriginAddress + 0x14);
		vOrigin[2] = *(float*)(vOriginAddress + 0x18);

		//std::cout << "X:" << vOrigin[0] << " Y:" << vOrigin[1] << " Z:" << vOrigin[2] << std::endl;
		return true;
	}
	return false;
}

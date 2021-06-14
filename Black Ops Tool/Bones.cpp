#include "Bones.h"

// Gets the in-game bone IDs
void Bones::RegisterBones()
{
	bones.clear();

	for (int i = 0; i < NUM_TAGS; i++)
	{
		WORD bone = (WORD) RegisterTag(tagNames[i].c_str(), 0);
		std::cout << tagNames[i] << ":" << bone << std::endl;
		bones.push_back(bone);
	}
}

// Gets bone position from zombies or bots
void Bones::GetEntityBones(DWORD pEnt, WORD wBone, vec3_t vOrigin)
{
	std::cout << "Client Num?: " << *(DWORD*)pEnt << std::endl;
	DWORD result = GetBoneInfo(*(DWORD*)pEnt, 0); // Gets BoneInfo from entity's client number
	std::cout << "Result: " << result << std::endl;
	if (result)
	{
		std::cout << "Getting bones!\n";
		GetTagPos((DWORD*)pEnt, result, wBone, vOrigin);
	}
}

// Gets bone position from real players
void Bones::GetPlayerBones(DWORD pPlayer, WORD wBone, vec3_t vOrigin)
{
	//DWORD result = UnknownTag(*(DWORD*)(pPlayer + 0x59), 0); // Gives player bones??
	DWORD result = GetBoneInfo(*(DWORD*)(pPlayer + 0x164), *(DWORD*)(pPlayer + 0x4));
	if (result)
	{
		GetTagPos((DWORD*)pPlayer, result, wBone, vOrigin);
	}
}

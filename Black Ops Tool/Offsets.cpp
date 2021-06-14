#include "Offsets.h"

// Pointer to the entity list
DWORD dwEntityList = 0x1BFBC84;

// Function for registering tag IDs
RegisterTag_t RegisterTag = (RegisterTag_t)0x55ABF0;

// Function for sending commands to console
CBuf_AddText_ CBuf_AddText = (CBuf_AddText_)0x49B930;

// Function for getting entity's bone information
BoneInfo_t GetBoneInfo = (BoneInfo_t)0x501850;

// Gets position of bone from bone information
GetTagPos_t GetTagPos = (GetTagPos_t)0x44A0A0;
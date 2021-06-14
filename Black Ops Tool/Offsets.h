#pragma once

#include <Windows.h>
#include "Structs.h"

extern DWORD dwEntityList;

typedef unsigned int(__cdecl* RegisterTag_t)(const char* boneName, int zero);
extern RegisterTag_t RegisterTag;

typedef int(__cdecl* CBuf_AddText_)(int zero, const char* text);
extern CBuf_AddText_ CBuf_AddText;

typedef DWORD(__cdecl* BoneInfo_t)(DWORD a1, DWORD a2);
extern BoneInfo_t GetBoneInfo;

typedef int(__cdecl* GetTagPos_t)(DWORD * entity, DWORD unknownResult, WORD bone, vec3_t origin);
extern GetTagPos_t GetTagPos;
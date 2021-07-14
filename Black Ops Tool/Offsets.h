#pragma once

#include <Windows.h>
#include "Structs.h"
#include "Entity.h"

extern DWORD dwEntityList;
extern DWORD dwMouseInput;
extern DWORD dwConsole;

typedef unsigned int(__cdecl* RegisterTag_t)(const char* boneName, int zero);
extern RegisterTag_t RegisterTag;

typedef int(__cdecl* CBuf_AddText_)(int zero, const char* text);
extern CBuf_AddText_ CBuf_AddText;

typedef void*(__cdecl* BoneInfo_t)(int a1, int a2);
extern BoneInfo_t GetBoneInfo;

typedef int(__cdecl* GetTagPos_t)(entity_t* entity, void* mesh, short tag, float * vOrigin);
extern GetTagPos_t GetTagPos;

typedef int(__cdecl* CG_Trace_t)(trace_t* trace, vec3_t start, vec3_t end, int skipNumber, int mask, int a6, int a7);
extern CG_Trace_t CGTrace;

typedef int (__cdecl* CG_ReturnTagPos_t)(int entityAddress, void* Mesh, short wBone);
extern CG_ReturnTagPos_t CG_ReturnTagPos;

typedef void(__cdecl* Cmd_AddServerCommand_t)(const char * command, int a2, int a3);
extern Cmd_AddServerCommand_t Cmd_AddServerCommand;

typedef void(__cdecl* Cmd_AddCommand_t)(const char * command, int a2, int a3);
extern Cmd_AddCommand_t Cmd_AddCommand;
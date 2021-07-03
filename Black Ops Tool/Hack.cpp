#include "Hack.h"


// Crosshair Settings
bool Hack::bDrawCrosshair = false;
bool Hack::bCrosshairDisabled = false;

float Hack::crosshairColor[3] = { 0.f, 1.f, 0.f };
float Hack::crosshairGap = 5.f;
float Hack::crosshairLength = 9.f;
float Hack::crosshairThickness = 1.5f;

// ESP Settings
bool Hack::bDrawESPBox = false;
float Hack::ESPBoxColor[3] = { 0.f, 1.f, 0.f };
bool Hack::bESPBoxRainbow = false;

bool Hack::bDrawESPLine = false;
bool Hack::bESPLineRainbow = false;
float Hack::ESPLineColor[3] = { 1.f, 0.f, 0.f };

bool Hack::bDrawDistanceESP = false;
float Hack::ESPDistanceColor[3] = { 0.f, 1.f, 0.f };

bool Hack::bDrawDistanceAlert = false;
float Hack::distanceAlertColor[3] = { 1.f, 0.f, 0.f };

bool Hack::bDrawESPBones = false;

int Hack::selectedItem = 0;

void Hack::HackLoop()
{
	Entity.GetEntities();

	//Loops through entities
	for (int i = 0; i < Entity.cgEntities.size(); i++)
	{
		if (Entity.cgEntities[i] != nullptr)
		{
			if (Entity.cgEntities[i]->isAlive)
			{
				if (bDrawESPBox || bDrawESPLine)
					Wall(Entity.cgEntities[i]);

				if(bDrawDistanceESP)
					DistanceESP(Entity.cgEntities[i]);

				if(bDrawDistanceAlert)
					EnemyDistanceAlert(Entity.cgEntities[i]);

				/*	[W.I.P]
				if (bDrawESPBones)
					DrawBoneESP(Entity.cgEntities[i]);
				*/
			}
		}
	}
	// Only draw crosshair when not aiming
	if (bDrawCrosshair)
	{
		// Disable game crosshair
		if (!bCrosshairDisabled) {
			cg_drawCrosshair->Value = 0;
			bCrosshairDisabled = true;
		}

		// If not aiming down sights
		if (localPlayer->ADS < 0.9)
		{
			Drawing.DrawCrosshair(crosshairGap, crosshairLength, crosshairThickness, 
				D3DCOLOR_ARGB(255, (int)(crosshairColor[0]*255.f), (int)(crosshairColor[1]*255.f), (int)(crosshairColor[2]*255.f)));
		}
	}
	// If custom crosshair is off, but crosshair is still disabled
	if (!bDrawCrosshair && bCrosshairDisabled)
	{
		cg_drawCrosshair->Value = 1;
		bCrosshairDisabled = false;
	}
}

void Hack::NoClip()
{
	CBuf_AddText(0, "noclip");
}

void Hack::God()
{
	CBuf_AddText(0, "god");
}

void Hack::GiveItem(int itemIndex)
{
	std::string command = "give " + itemNames[itemIndex];
	CBuf_AddText(0, command.c_str());
}

void Hack::EnemyDistanceAlert(entity_t* pEnt)
{
	// Gets the distance from the enemy
	float distanceFromEnemy = sqrtf(localPlayer->WorldPos[0] - pEnt->WorldPos[0]  * (localPlayer->WorldPos[0] - pEnt->WorldPos[0])
						+ (localPlayer->WorldPos[1] - pEnt->WorldPos[1]) * (localPlayer->WorldPos[1] - pEnt->WorldPos[1])
						+ (localPlayer->WorldPos[2] - pEnt->WorldPos[2]) * (localPlayer->WorldPos[2] - pEnt->WorldPos[2]));

	if (distanceFromEnemy < 160.f)
	{
		Drawing.DrawFont("ENEMY CLOSE", refdef->screenWidth / 2, refdef->screenHeight - 250, 
			D3DCOLOR_ARGB(255, int(distanceAlertColor[0] * 255), int(distanceAlertColor[1] * 255), int(distanceAlertColor[2] * 255)));
	}
}

// Rainbow ESP
/* // W.I.P
void Hack::RainbowESP()
{
	// Index Reset
	if (colorIndex == 3)
		colorIndex = 0;

	// Update Color
	ESPBoxColor[colorIndex] += 0.01;

	// Swap Color
	if (ESPBoxColor[colorIndex] >= 1.f)
	{
		// Reset Color
		ESPBoxColor[colorIndex] == 0.f;

		colorIndex += 1;
	}
}
*/

void Hack::DrawBoneESP(entity_t* pEnt)
{
	BoneESP(pEnt, Bones.bones[j_helmet], Bones.bones[j_neck]);
	BoneESP(pEnt, Bones.bones[j_neck], Bones.bones[j_shoulder_le]);
	BoneESP(pEnt, Bones.bones[j_neck], Bones.bones[j_shoulder_ri]);
	BoneESP(pEnt, Bones.bones[j_shoulder_le], Bones.bones[j_elbow_le]);
	BoneESP(pEnt, Bones.bones[j_shoulder_ri], Bones.bones[j_elbow_ri]);
	BoneESP(pEnt, Bones.bones[j_elbow_le], Bones.bones[j_wrist_le]);
	BoneESP(pEnt, Bones.bones[j_elbow_ri], Bones.bones[j_wrist_ri]);
	BoneESP(pEnt, Bones.bones[j_neck], Bones.bones[j_mainroot]);

	BoneESP(pEnt, Bones.bones[j_mainroot], Bones.bones[j_hip_le]);
	BoneESP(pEnt, Bones.bones[j_mainroot], Bones.bones[j_hip_ri]);

	BoneESP(pEnt, Bones.bones[j_hip_le], Bones.bones[j_knee_le]);
	BoneESP(pEnt, Bones.bones[j_hip_ri], Bones.bones[j_knee_ri]);
	BoneESP(pEnt, Bones.bones[j_knee_le], Bones.bones[j_ankle_le]);
	BoneESP(pEnt, Bones.bones[j_knee_ri], Bones.bones[j_ankle_ri]);
}
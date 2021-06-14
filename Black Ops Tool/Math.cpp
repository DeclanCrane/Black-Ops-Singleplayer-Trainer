#include "Math.h"

void GetAngleToTarget(vec3_t& vTargetPos, vec3_t& vCameraPos, vec3_t& vAngles)
{
	vec3_t vDelta;
	vDelta[0] = vTargetPos[0] - vCameraPos[0];
	vDelta[1] = vTargetPos[1] - vCameraPos[1];
	vDelta[2] = vTargetPos[2] - vCameraPos[2];

	VectorAngles(vDelta, vAngles);
}

void VectorAngles(const vec3_t& forward, vec3_t& angles)
{
	float tmp, yaw, pitch;

	if (forward[1] == 0 && forward[0] == 0)
	{
		yaw = 0;
		if (forward[2] > 0)
			pitch = 270;
		else
			pitch = 90;
	}
	else
	{
		yaw = (atan2f(forward[1], forward[0]) * 180.0 / M_PI);
		if (yaw < 0)
			yaw += 360;

		tmp = sqrtf(forward[0] * forward[0] + forward[1] * forward[1]);
		pitch = (atan2f(-forward[2], tmp) * 180.0 / M_PI);
		if (pitch < 0)
			pitch += 360;
	}

	angles[0] = yaw;
	angles[1] = pitch;
	angles[2] = 0;
}

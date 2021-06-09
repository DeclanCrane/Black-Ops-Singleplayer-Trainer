#include "Vector.h"


// SAMPLE WORLD TO SCREEN
//bool WorldToScreen(vec3_t world, float* x, float* y)
//{
//	vec3_t Position = VectorSubtract(world, RefDef->eyePos);
//	vec3_t Transform;
//
//	// get our dot products from viewAxis
//	Transform.x = DotProduct(Position, RefDef->viewAxis[1]);
//	Transform.y = DotProduct(Position, RefDef->viewAxis[2]);
//	Transform.z = DotProduct(Position, RefDef->viewAxis[0]);
//
//	// make sure it is in front of us
//	if (Transform.z < 0.1f)
//		return false;
//
//	// get the center of the screen
//	vec2_t Center = vec2_t((float)RefDef->scrWidth * 0.5f, (float)RefDef->scrHeight * 0.5f);
//
//	*x = Center.x * (1 - (Transform.x / RefDef->fov.x / Transform.z));
//	*y = Center.y * (1 - (Transform.y / RefDef->fov.y / Transform.z));
//	return true;
//}
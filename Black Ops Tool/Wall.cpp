#include "Wall.h"
#include <math.h>

//DOESNT SEEM TO WORK PROPERLY
//bool WorldToScreen(vec3_t vWorldLocation, float Screen[2])
//{
//	vec3_t vLocal, vTransForm;
//	VectorSubtract(vWorldLocation, refdef->eyePosition, vLocal);
//
//	vTransForm[0] = DotProduct(vLocal, refdef->viewAxis[1]);
//	vTransForm[1] = DotProduct(vLocal, refdef->viewAxis[2]);
//	vTransForm[2] = DotProduct(vLocal, refdef->viewAxis[0]);
//
//	if (vTransForm[2] < 0.01f) {
//		return false;
//	}
//
//	Screen[0] = ((refdef->screenWidth / 2) * (1 - (vTransForm[0] / refdef->fov[0] / vTransForm[2])));
//	Screen[1] = ((refdef->screenHeight / 2) * (1 - (vTransForm[1] / refdef->fov[1] / vTransForm[2])));
//
//	return true;
//}

//SAMPLE WORLD TO SCREEN
bool WorldToScreen(vec3_t world, vec2_t& screen)
{
	vec3_t Position;
	VectorSubtract(world, refdef->eyePosition, Position);
	vec3_t Transform;

	// get our dot products from viewAxis
	Transform[0] = DotProduct(Position, refdef->viewAxis[1]);
	Transform[1] = DotProduct(Position, refdef->viewAxis[2]);
	Transform[2] = DotProduct(Position, refdef->viewAxis[0]);


	// make sure it is in front of us
	if (Transform[2] < 0.1f)
		return false;

	// get the center of the screen
	//vec2_t Center = vec2_t((float)RefDef->scrWidth * 0.5f, (float)RefDef->scrHeight * 0.5f);
	vec2_t CenterScreen;
	CenterScreen[0] = refdef->screenWidth / 2;
	CenterScreen[1] = refdef->screenHeight / 2;

	screen[0] = CenterScreen[0] * (1 - (Transform[0] / refdef->fovX / Transform[2]));
	screen[1] = CenterScreen[1] * (1 - (Transform[1] / refdef->fov[0] / Transform[2]));
	return true;
}

//Thanks to c5 for this knowledge GUIDED HACKING FUNCTION
//bool WorldToScreen(vec3_t src, vec3_t dst, vec2_t& screen, float fovx, float fovy, float windowWidth, float windowHeight, vec3_t left, vec3_t up, vec3_t forward)
//{
//    vec3_t transform;
//    float xc, yc;
//    float px, py;
//    float z;
//
//    px = tan(fovx * PI / 360.0);
//    py = tan(fovy * PI / 360.0);
//
//    VectorSubtract(dst, src, transform);
//
//    xc = windowWidth / 2.0;
//    yc = windowHeight / 2.0;
//
//    z = DotProduct(transform, left);
//
//    if (z <= 0.1)
//    {
//        return false;
//    }
//
//    screen[0] = xc - DotProduct(transform, up) * xc / (z * px);
//    screen[1] = yc - DotProduct(transform, forward) * yc / (z * py);
//
//    return true;
//}
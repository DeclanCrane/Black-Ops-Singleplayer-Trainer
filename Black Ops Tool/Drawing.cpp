#include "Drawing.h"
#include <iostream>

Drawing_t Drawing;


Drawing_t::Drawing_t()
{
	pDevice		= nullptr;
	lineL		= nullptr;
	font		= nullptr;
}

Drawing_t::~Drawing_t()
{
	if(lineL)
		lineL->Release();

	if(font)
		font->Release();
}

void Drawing_t::DrawFilledRect(int screenX, int screenY, int rectWidth, int rectHeight, D3DCOLOR color)
{
	D3DRECT rect = { screenX, screenY, screenX + rectWidth, screenY + rectHeight };
	pDevice->Clear(1, &rect, D3DCLEAR_TARGET, color, 0, 0);
}

void Drawing_t::DrawLine(int x1, int y1, int x2, int y2, int thickness, D3DCOLOR color)
{
	// Only creates line once
	if(!lineL)
		D3DXCreateLine(pDevice, &lineL);

	D3DXVECTOR2 Line[2];

	Line[0] = D3DXVECTOR2(x1, y1);
	Line[1] = D3DXVECTOR2(x2, y2);

	lineL->SetWidth(thickness);
	lineL->Draw(Line, 2, color);
}

void Drawing_t::DrawLine(vec2_t src, vec2_t dst, int thickness, D3DCOLOR color)
{
	DrawLine(src[0], src[1], dst[0], dst[1], thickness, color);
}

void Drawing_t::DrawEspBox2D(vec2_t top, vec2_t bottom, int thickness, D3DCOLOR color)
{
	int height = ABS(top[1] - bottom[1]);
	vec2_t topLeft, topRight;
	topLeft[0] = top[0] - height / 4;
	topRight[0] = top[0] + height / 4;
	topLeft[1] = topRight[1] = top[1];

	vec2_t bottomLeft, bottomRight;
	bottomLeft[0] = bottom[0] - height / 4;
	bottomRight[0] = bottom[0] + height / 4;
	bottomLeft[1] = bottomRight[1] = bottom[1];

	DrawLine(topLeft, topRight, thickness, color);
	DrawLine(bottomLeft, bottomRight, thickness, color);
	DrawLine(topLeft, bottomLeft, thickness, color);
	DrawLine(topRight, bottomRight, thickness, color);
}

void Drawing_t::DrawFont(const char* text, float x, float y, D3DCOLOR color)
{
	// Only creates font once
	if(!font)
		D3DXCreateFont(pDevice, 14, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET, 
			OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Arial", &font);

	RECT rect;

	// Draw shadow behind text
	SetRect(&rect, x + 1, y + 1, x + 1, y + 1);
	font->DrawTextA(NULL, text, -1, &rect, DT_CENTER | DT_NOCLIP, D3DCOLOR_ARGB(255, 0, 0, 0));

	SetRect(&rect, x, y, x, y);
	font->DrawTextA(NULL, text, -1, &rect, DT_CENTER | DT_NOCLIP, color);
}

void Drawing_t::DrawCrosshair(float gap, float length, float thickness, D3DCOLOR color)
{
	// Get center of screen
	vec2_t screenCenter;
	screenCenter[0] = refdef->screenWidth / 2;
	screenCenter[1] = refdef->screenHeight / 2;

	vec2_t src, dst;
	src[0] = (screenCenter[0] - gap);
	src[1] = screenCenter[1];
	dst[0] = (src[0] - length);
	dst[1] = src[1];

	//Left
	DrawLine(src, dst, thickness, color);

	src[0] = (screenCenter[0] + gap);
	src[1] = screenCenter[1];
	dst[0] = (src[0] + length);
	dst[1] = src[1];

	//Right
	DrawLine(src, dst, thickness, color);

	src[1] = (screenCenter[1] - gap);
	src[0] = screenCenter[0];
	dst[1] = (src[1] - length);
	dst[0] = src[0];

	// Top
	DrawLine(src, dst, thickness, color);

	src[1] = (screenCenter[1] + gap);
	src[0] = screenCenter[0];
	dst[1] = (src[1] + length);
	dst[0] = src[0];

	// Bottom
	DrawLine(src, dst, thickness, color);
}

#include "Drawing.h"
#include <iostream>

void DrawFilledRect(int screenX, int screenY, int rectWidth, int rectHeight, D3DCOLOR color, IDirect3DDevice9* pDevice)
{
	D3DRECT rect = { screenX, screenY, screenX + rectWidth, screenY + rectHeight };
	pDevice->Clear(1, &rect, D3DCLEAR_TARGET, color, 0, 0);
}

void DrawLine(int x1, int y1, int x2, int y2, int thickness, D3DCOLOR color, IDirect3DDevice9* pDevice)
{
	ID3DXLine* lineL;
	D3DXCreateLine(pDevice, &lineL);

	D3DXVECTOR2 Line[2];

	Line[0] = D3DXVECTOR2(x1, y1);
	Line[1] = D3DXVECTOR2(x2, y2);

	lineL->SetWidth(thickness);
	lineL->Draw(Line, 2, color);
	lineL->Release();
}

void DrawLine(vec2_t src, vec2_t dst, int thickness, D3DCOLOR color, IDirect3DDevice9* pDevice)
{
	DrawLine(src[0], src[1], dst[0], dst[1], thickness, color, pDevice);
}

void DrawEspBox2D(vec2_t top, vec2_t bottom, int thickness, D3DCOLOR color, IDirect3DDevice9* pDevice)
{
	int height = ABS(top[1] - bottom[1]);
	vec2_t tl, tr;
	tl[0] = top[0] - height / 4;
	tr[0] = top[0] + height / 4;
	tl[1] = tr[1] = top[1];

	vec2_t bl, br;
	bl[0] = bottom[0] - height / 4;
	br[0] = bottom[0] + height / 4;
	bl[1] = br[1] = bottom[1];

	DrawLine(tl, tr, thickness, color, pDevice);
	DrawLine(bl, br, thickness, color, pDevice);
	DrawLine(tl, bl, thickness, color, pDevice);
	DrawLine(tr, br, thickness, color, pDevice);
}

void DrawFont(const char* text, float x, float y, D3DCOLOR color, ID3DXFont * font, IDirect3DDevice9* pDevice)
{
	RECT rect;
	font = nullptr;

	if (!font)
		D3DXCreateFont(pDevice, 14, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Arial", &font);

	SetRect(&rect, x + 1, y + 1, x + 1, y + 1);
	font->DrawTextA(NULL, text, -1, &rect, DT_CENTER | DT_NOCLIP, D3DCOLOR_ARGB(255, 0, 0, 0));

	SetRect(&rect, x, y, x, y);
	font->DrawTextA(NULL, text, -1, &rect, DT_CENTER | DT_NOCLIP, color);
}

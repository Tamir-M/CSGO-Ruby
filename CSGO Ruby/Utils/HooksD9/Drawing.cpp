#include "Drawing.h"
#include "../../Feature/HackFeatures.h"

ID3DXLine* LineL;

void DrawFilledRect(int x, int y, int w, int h, D3DCOLOR color)
{
	D3DRECT rect = { x,y,x + w,y + h };
	pDevice->Clear(1, &rect, D3DCLEAR_TARGET, color, 0, 0);
}

void DrawLine(float x1, float y1, float x2, float y2, FLOAT thickness, D3DCOLOR color) {
	if(!LineL)
		D3DXCreateLine(pDevice, &LineL);

	D3DXVECTOR2 Line[2];
	Line[0] = D3DXVECTOR2(x1, y1);
	Line[1] = D3DXVECTOR2(x2, y2);
	LineL->SetWidth(thickness);
	LineL->Draw(Line, 2, color);
}

void DrawLine(Vec2 src, Vec2 dst, FLOAT thickness, D3DCOLOR color) {
	DrawLine(src.x, src.y, dst.x, dst.y, thickness, color);
}

void DrawESPBox2D(Vec2 top, Vec2 bot, FLOAT thickness, D3DCOLOR color) {
	float height = ABS(top.y - bot.y);

	Vec2 tl, tr;
	tl.x = top.x - height / 4;
	tr.x = top.x + height / 4;
	tl.y = tr.y = top.y;

	Vec2 bl, br;
	bl.x = bot.x - height / 4;
	br.x = bot.x + height / 4;
	bl.y = br.y = bot.y;

	DrawLine(tl, tr, thickness, color);
	DrawLine(bl, br, thickness, color);
	DrawLine(tl, bl, thickness, color);
	DrawLine(tr, br, thickness, color);
}

void DrawESPBox3D(Vec3 top, Vec3 bot, FLOAT a, int width, FLOAT thickness, D3DCOLOR color) {
	float height3D = ABS(top.z - bot.z);
	Vec3 b1, b2, b3, b4, t1, t2, t3, t4;
	b1.z = b2.z = b3.z = b4.z = bot.z;

	b1.x = bot.x + (cosf(TORAD(a + 45)) * width);
	b1.y = bot.y + (sinf(TORAD(a + 45)) * width);
	
	b2.x = bot.x + (cosf(TORAD(a + 135)) * width);
	b2.y = bot.y + (sinf(TORAD(a + 135)) * width);
	
	b3.x = bot.x + (cosf(TORAD(a + 225)) * width);
	b3.y = bot.y + (sinf(TORAD(a + 225)) * width);
	
	b4.x = bot.x + (cosf(TORAD(a + 315)) * width);
	b4.y = bot.y + (sinf(TORAD(a + 315)) * width);

	t1.x = b1.x;
	t1.y = b1.y;
	t1.z = b1.z + height3D;
	
	t2.x = b2.x;
	t2.y = b2.y;
	t2.z = b2.z + height3D;
	
	t3.x = b3.x;
	t3.y = b3.y;
	t3.z = b3.z + height3D;
	
	t4.x = b4.x;
	t4.y = b4.y;
	t4.z = b4.z + height3D;

	Vec2 b1_2, b2_2, b3_2, b4_2, t1_2, t2_2, t3_2, t4_2;

	if (ESPHack->WorldToScreen(b1, b1_2) && ESPHack->WorldToScreen(b2, b2_2)
		&& ESPHack->WorldToScreen(b3, b3_2) && ESPHack->WorldToScreen(b4, b4_2)
		&& ESPHack->WorldToScreen(t1, t1_2) && ESPHack->WorldToScreen(t2, t2_2)
		&& ESPHack->WorldToScreen(t3, t3_2) && ESPHack->WorldToScreen(t4, t4_2)) {

		// col
		DrawLine(t1_2, b1_2, thickness, color);
		DrawLine(t2_2, b2_2, thickness, color);
		DrawLine(t3_2, b3_2, thickness, color);
		DrawLine(t4_2, b4_2, thickness, color);

		// top base
		DrawLine(t1_2, t2_2, thickness, color);
		DrawLine(t2_2, t3_2, thickness, color);
		DrawLine(t3_2, t4_2, thickness, color);
		DrawLine(t4_2, t1_2, thickness, color);
		
		// bottom base
		DrawLine(b1_2, b2_2, thickness, color);
		DrawLine(b2_2, b3_2, thickness, color);
		DrawLine(b3_2, b4_2, thickness, color);
		DrawLine(b4_2, b1_2, thickness, color);
	}
}

void DrawText2D(const char* text, float x, float y, D3DCOLOR color, int alignment) {
	RECT rect;

	if (!ESPHack->Font)
		D3DXCreateFont(pDevice, 14, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Consolas", &ESPHack->Font);

	SetRect(&rect, x + 1, y + 1, x + 1, y + 1);
	ESPHack->Font->DrawTextA(NULL, text, -1, &rect, alignment | DT_NOCLIP, D3DCOLOR_ARGB(255,0,0,0));
	
	SetRect(&rect, x, y, x, y);
	ESPHack->Font->DrawTextA(NULL, text, -1, &rect, alignment | DT_NOCLIP, color);

}

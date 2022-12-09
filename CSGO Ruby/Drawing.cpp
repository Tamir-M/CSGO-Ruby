#include "Drawing.h"

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

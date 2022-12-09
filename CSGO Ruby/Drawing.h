#pragma once
#include "dx.h"
#include "Vector.h"
#include "Values.h"

#define ABS(x) ((x < 0) ? (-x) : (x))

extern ID3DXLine* LineL;

void DrawFilledRect(int x, int y, int w, int h, D3DCOLOR color);

void DrawLine(float x1, float y1, float x2, float y2, FLOAT thickness, D3DCOLOR color);
void DrawLine(Vec2 src, Vec2 dst, FLOAT thickness, D3DCOLOR color);

void DrawESPBox2D(Vec2 top, Vec2 bot, FLOAT thickness, D3DCOLOR color);
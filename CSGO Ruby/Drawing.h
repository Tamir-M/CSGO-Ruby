#pragma once
#include "dx.h"
#include "Vector.h"

#define ABS(x) ((x < 0) ? (-x) : (x))
#define TORAD(x) ((x) * static_cast<float>(0.01745329252))

extern ID3DXLine* LineL;

void DrawFilledRect(int x, int y, int w, int h, D3DCOLOR color);

void DrawLine(float x1, float y1, float x2, float y2, FLOAT thickness, D3DCOLOR color);
void DrawLine(Vec2 src, Vec2 dst, FLOAT thickness, D3DCOLOR color);

void DrawESPBox2D(Vec2 top, Vec2 bot, FLOAT thickness, D3DCOLOR color);

void DrawESPBox3D(Vec3 top, Vec3 bot, FLOAT a, int width, FLOAT thickness, D3DCOLOR color);

void DrawText2D(const char* text, float x, float y, D3DCOLOR color, int alignment = DT_CENTER);
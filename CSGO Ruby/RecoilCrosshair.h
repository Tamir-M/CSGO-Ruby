#pragma once
#include "Feature.h"
#include "Vector.h"
#include "Drawing.h"

class RecoilCrosshair: public Feature {
public:
	Vec2 crosshair2D;
	int crosshairSize = 4;
	void Draw();
	void CalcRecoil();
};
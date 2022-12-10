#pragma once
#include "../Baseline/Feature.h"
#include "../../Utils/Vector.h"
#include "../../Utils/HooksD9/Drawing.h"

class RecoilCrosshair: public Feature {
public:
	Vec2 crosshair2D;
	int crosshairSize = 4;
	void Draw();
	void CalcRecoil();
};
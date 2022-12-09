#include "RecoilCrosshair.h"

void RecoilCrosshair::Draw() {
	if (!this->isActive) return;

	Vec2 l, r, t, b;
	l = r = t = b = this->crosshair2D;
	l.x -= this->crosshairSize;
	r.x += this->crosshairSize;
	b.y += this->crosshairSize;
	t.y -= this->crosshairSize;

	DrawLine(l, r, 2, D3DCOLOR_ARGB(255, 255, 255, 255));
	DrawLine(t, b, 2, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void RecoilCrosshair::CalcRecoil() {
	Vec3* pAng = (Vec3*)(localPlayer + m_aimPunchAngle);

	this->crosshair2D.x = windowWidth / 2 - (windowWidth / 90 * pAng->y);
	this->crosshair2D.y = windowHeight / 2 + (windowHeight / 90 * pAng->x);
}
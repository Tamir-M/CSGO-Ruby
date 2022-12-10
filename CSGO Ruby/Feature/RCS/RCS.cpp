#include "RCS.h"

void RCS::Init() {
	this->viewAngles = (Vec3*)(*(uintptr_t*)(engineModule + dwClientState) + dwClientState_ViewAngles);

	this->iShotsFired = (int*)(localPlayer + m_iShotsFired);

	this->aimPunchAngle = (Vec3*)(localPlayer + m_aimPunchAngle);

	this->oPunch = { 0,0,0 };
}

void RCS::Run() {
	if (!this->isActive) return;
	Vec3 punchAngle = *(this->aimPunchAngle) * 2;

	if (*(this->iShotsFired) > 1) {
		Vec3 newAngle = *(this->viewAngles) + this->oPunch - punchAngle;

		newAngle.Normalize();

		*(this->viewAngles) = newAngle;
	}

	this->oPunch = punchAngle;
}
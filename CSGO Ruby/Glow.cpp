#include "Glow.h"

void Glow::Run() {

	int localPlayerTeam = *(uintptr_t*)(localPlayer + m_iTeamNum);

	if (!this->isActive) return;
	for (unsigned short int i = 0; i < 64; ++i) {
		uintptr_t entity = *(uintptr_t*)(clientModule + dwEntityList + (i * 0x10));

		if (entity == NULL) break;

		int entityTeam = *(uintptr_t*)(entity + m_iTeamNum);

		if (localPlayerTeam == entityTeam) this->SetTeamGlow(entity);
		else this->SetEnemyGlow(entity);
	}
}

GlowStruct Glow::SetGlowColor(GlowStruct Glow, uintptr_t entity) {
	Glow.renderWhenOccluded = true;
	Glow.renderWhenUnoccluded = false;

	int health = *(int*)(entity + m_iHealth);
	bool isDefusing = *(bool*)(entity + m_bIsDefusing);

	if (isDefusing) {
		Glow.red = 1.0f;
		Glow.blue = 1.0f;
		Glow.green = 1.0f;
		Glow.alpha = 1.0f;
		return Glow;
	}
	Glow.red = health * -0.01f + 1;
	Glow.green = health * 0.01f;
	Glow.blue = 0.0f;
	Glow.alpha = 1.0f;
	return Glow;
}

void Glow::SetTeamGlow(uintptr_t entity) {
	int glowIdx = *(uintptr_t*)(entity + m_iGlowIndex);
	GlowStruct Glow = *(GlowStruct*)(GlowObject + (glowIdx * 0x38));

	Glow.blue = 1.0f;
	Glow.alpha = 1.0f;
	Glow.renderWhenOccluded = true;
	Glow.renderWhenUnoccluded = false;

	*(GlowStruct*)(GlowObject + (glowIdx * 0x38)) = Glow;
}

void Glow::SetEnemyGlow(uintptr_t entity) {
	int glowIdx = *(uintptr_t*)(entity + m_iGlowIndex);
	GlowStruct Glow = *(GlowStruct*)(GlowObject + (glowIdx * 0x38));

	*(GlowStruct*)(GlowObject + (glowIdx * 0x38)) = SetGlowColor(Glow, entity);
}
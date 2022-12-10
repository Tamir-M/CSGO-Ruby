#pragma once
#include "../Baseline/Feature.h"

struct GlowStruct {
	BYTE base[8];
	float red;
	float green;
	float blue;
	float alpha;
	BYTE buffer[16];
	bool renderWhenOccluded;
	bool renderWhenUnoccluded;
	bool fullBloom;
	BYTE buffer1[5];
	int glowStyle;
};

class Glow : public Feature
{
public:
	using Feature::Feature;
	void Run();
private:
	GlowStruct SetGlowColor(GlowStruct Glow, uintptr_t entity);
	void SetTeamGlow(uintptr_t entity);
	void SetEnemyGlow(uintptr_t entity);
};


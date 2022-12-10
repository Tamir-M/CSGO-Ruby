#pragma once
#include "../../Utils/HooksD9/dx.h"
#include "../Baseline/Feature.h"
#include "../../Utils/Vector.h"
#include "../../Utils/Values/Values.h"
#include "../../Utils/HooksD9/Drawing.h"
#include <sstream>
#include <string>

#define STR_MERGE_IMPL(a, b) a##b
#define STR_MERGE(a, b) STR_MERGE_IMPL(a, b)
#define MAKE_PAD(size) STR_MERGE(_pad, __COUNTER__)[size]
#define DEFINE_MEMBER_N(type, name, offset) struct { unsigned char MAKE_PAD(offset); type name; }

class Ent {
public:
	union {
		DEFINE_MEMBER_N(bool, isDormant, m_bDormant);
		DEFINE_MEMBER_N(int, iHealth, m_iHealth);
		DEFINE_MEMBER_N(Vec3, vecOrigin, m_vecOrigin);
		DEFINE_MEMBER_N(int, iTeamNum, m_iTeamNum);
		DEFINE_MEMBER_N(int, boneMatrix, m_dwBoneMatrix);
		DEFINE_MEMBER_N(int, armorValue, m_ArmorValue);
		DEFINE_MEMBER_N(Vec3, aimPunchAngle, m_aimPunchAngle);
		DEFINE_MEMBER_N(float, angEyeAnglesX, m_angEyeAnglesX);
		DEFINE_MEMBER_N(float, angEyeAnglesY, m_angEyeAnglesY);
		DEFINE_MEMBER_N(Vec3, vecVelocity, m_vecVelocity);
		DEFINE_MEMBER_N(bool, bHasHelmet, m_bHasHelmet);
	};
};

class EntListObj {
public:
	Ent* ent;
	char padding[12];
};

class EntList {
public:
	EntListObj ents[32];
};

class ESP: public Feature {
public:
	Ent* localEnt;
	EntList* entList;
	float viewMatrix[16];
	ID3DXFont* Font;
	

public:
	~ESP();
	void Init();
	void Run();
	bool CheckValidEnt(Ent* ent);
	bool WorldToScreen(Vec3 pos, Vec2& screen);
	void Draw();
	Vec3 GetBonePos(Ent* ent, int bone);
	Vec3 TransformVec(Vec3 src, Vec3 ang, float distance);
	struct settings {
		bool showTeammates = false;
		bool snapLines = false;
		bool box2D = false;
		bool status2D = false;
		bool statusText = false;
		bool box3D = false;
		bool headlineESP = false;
	}settings;
};

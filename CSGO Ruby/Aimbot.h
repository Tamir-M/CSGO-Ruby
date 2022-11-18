#pragma once

#include "Feature.h"
#include "Vector.h"

#define PI 3.14159265358

class Aimbot : public Feature
{
public:
	using Feature::Feature;
	void Run();
private:
	uintptr_t* GetClosestEnemy();
	void AimAt(Vec3* target);
};


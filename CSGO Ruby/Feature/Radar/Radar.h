#pragma once

#include "../Baseline/Feature.h"

class Radar : public Feature
{
public:
	using Feature::Feature;
	void Run();
};


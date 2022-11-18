#pragma once

#include "Feature.h"

class Radar : public Feature
{
public:
	using Feature::Feature;
	void Run();
};


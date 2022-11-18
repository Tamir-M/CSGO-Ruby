#pragma once

#include "Feature.h"

#define FL_ONGROUND (1 >> 0)

class BHop : public Feature
{
public:
	using Feature::Feature;
	void Run();
};


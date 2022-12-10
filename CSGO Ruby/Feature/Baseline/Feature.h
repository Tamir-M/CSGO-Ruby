#pragma once
#include <Windows.h>

#include "../../Utils/Values/Values.h"

class Feature
{
public:
	bool isActive;

	Feature();

	void Toggle();
};


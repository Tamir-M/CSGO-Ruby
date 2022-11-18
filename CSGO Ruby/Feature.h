#pragma once
#include <Windows.h>

#include "Values.h"

class Feature
{
public:
	bool isActive;

	Feature();

	void Toggle();
};


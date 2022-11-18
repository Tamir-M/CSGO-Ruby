#pragma once
#include <Windows.h>

#include "Values.h"

extern class Feature
{
public:
	bool isActive;

	Feature();

	void Toggle();
};


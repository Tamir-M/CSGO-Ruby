#include "Feature.h"

void Feature::Toggle()
{
	this->isActive = !this->isActive;
}


Feature::Feature() {
	this->isActive = false;
}
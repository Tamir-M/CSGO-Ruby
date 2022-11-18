#include "HackFeatures.h"

BHop BunnyHop;

void InitHackFeatures() {
	BunnyHop = BHop();
}

void HackToggles() {
	if (GetAsyncKeyState(VK_NUMPAD1) & 1)
		BunnyHop.Toggle();
}
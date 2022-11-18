#include "HackFeatures.h"

BHop BunnyHop;
AntiFlash FlashHack;
Radar RadarHack;

void InitHackFeatures() {
	BunnyHop = BHop();
	FlashHack = AntiFlash();
	RadarHack = Radar();
}

void HackToggles() {
	if (GetAsyncKeyState(VK_NUMPAD1) & 1)
		BunnyHop.Toggle();
	if (GetAsyncKeyState(VK_NUMPAD2) & 1)
		FlashHack.Toggle();
	if (GetAsyncKeyState(VK_NUMPAD3) & 1)
		RadarHack.Toggle();
}

void HackRuns() {
	BunnyHop.Run();
	FlashHack.Run();
	RadarHack.Run();
}
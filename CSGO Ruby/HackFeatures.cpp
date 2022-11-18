#include "HackFeatures.h"

BHop BunnyHop;
AntiFlash FlashHack;
Radar RadarHack;
Glow GlowHack;

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
	if (GetAsyncKeyState(VK_NUMPAD4) & 1)
		GlowHack.Toggle();
}

void HackRuns() {
	BunnyHop.Run();
	FlashHack.Run();
	RadarHack.Run();
	GlowHack.Run();
}
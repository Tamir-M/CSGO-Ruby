#include "HackFeatures.h"

BHop BunnyHop;
AntiFlash FlashHack;
Radar RadarHack;
Glow GlowHack;
RCS RCSHack;

void InitHackFeatures() {
	BunnyHop = BHop();
	FlashHack = AntiFlash();
	RadarHack = Radar();
	RCSHack = RCS();
	RCSHack.Init();
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
	if (GetAsyncKeyState(VK_NUMPAD5) & 1)
		RCSHack.Toggle();
}

void HackRuns() {
	BunnyHop.Run();
	FlashHack.Run();
	RadarHack.Run();
	GlowHack.Run();
	RCSHack.Run();
}
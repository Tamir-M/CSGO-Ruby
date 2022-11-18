#include "HackFeatures.h"

BHop BunnyHop;
AntiFlash FlashHack;

void InitHackFeatures() {
	BunnyHop = BHop();
	FlashHack = AntiFlash();
}

void HackToggles() {
	if (GetAsyncKeyState(VK_NUMPAD1) & 1)
		BunnyHop.Toggle();
	if (GetAsyncKeyState(VK_NUMPAD2) & 1)
		FlashHack.Toggle();
}

void HackRuns() {
	BunnyHop.Run();
	FlashHack.Run();
}
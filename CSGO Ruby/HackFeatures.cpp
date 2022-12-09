#include "HackFeatures.h"

BHop BunnyHop;
AntiFlash FlashHack;
Radar RadarHack;
Glow GlowHack;
RCS RCSHack;
Aimbot AimbotHack;
ESP* ESPHack;
RecoilCrosshair* rCrosshairHack;

void InitHackFeatures() {
	BunnyHop = BHop();
	FlashHack = AntiFlash();
	RadarHack = Radar();
	RCSHack = RCS();
	RCSHack.Init();
	AimbotHack = Aimbot();
	ESPHack = new ESP();
	ESPHack->Init();
	rCrosshairHack = new RecoilCrosshair();
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
	if (GetAsyncKeyState(VK_NUMPAD6) & 1)
		AimbotHack.Toggle();
	if (GetAsyncKeyState(VK_NUMPAD7) & 1)
		ESPHack->Toggle();
	if (GetAsyncKeyState(VK_NUMPAD8) & 1)
		rCrosshairHack->Toggle();
}

void HackRuns() {
	BunnyHop.Run();
	FlashHack.Run();
	RadarHack.Run();
	GlowHack.Run();
	RCSHack.Run();
	AimbotHack.Run();
	ESPHack->Run();
	rCrosshairHack->CalcRecoil();
}
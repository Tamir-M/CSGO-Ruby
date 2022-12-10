#pragma once
#include "./BHop/BHop.h"
#include "./AntiFlash/AntiFlash.h"
#include "./Radar/Radar.h"
#include "./Glow/Glow.h"
#include "./RCS/RCS.h"
#include "./Aimbot/Aimbot.h"
#include "./ESP/ESP.h"
#include "./RecoilCrosshair/RecoilCrosshair.h"

extern BHop BunnyHop;
extern AntiFlash FlashHack;
extern Radar RadarHack;
extern Glow GlowHack;
extern RCS RCSHack;
extern Aimbot AimbotHack;
extern ESP* ESPHack;
extern RecoilCrosshair* rCrosshairHack;

void InitHackFeatures();

void HackToggles();

void HackRuns();
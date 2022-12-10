#pragma once
#include <Windows.h>

#include "csgo.hpp"

using namespace hazedumper::netvars;
using namespace hazedumper::signatures;

extern uintptr_t clientModule;
extern uintptr_t localPlayer;
extern uintptr_t flags;
extern uintptr_t glowObject;
extern uintptr_t engineModule;

namespace Values {
	extern void InitPreGame();
	extern void InitInGame();
}
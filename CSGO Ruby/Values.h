#include <Windows.h>

#include "csgo.hpp"

using namespace hazedumper::netvars;
using namespace hazedumper::signatures;

extern uintptr_t clientModule;
extern uintptr_t localPlayer;
extern uintptr_t flags;

namespace Values {
	extern void InitPreGame();
	extern void InitInGame();
}
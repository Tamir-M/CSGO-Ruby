#include "Values.h"

uintptr_t flags;
uintptr_t localPlayer;
uintptr_t clientModule;
uintptr_t glowObject;
uintptr_t engineModule;

void Values::InitInGame() {
	flags = *(uintptr_t*)(localPlayer + m_fFlags);
	glowObject = *(uintptr_t*)(clientModule + dwGlowObjectManager);
}

void Values::InitPreGame() {
	clientModule = (uintptr_t)GetModuleHandle(L"client.dll");
	engineModule = (uintptr_t)GetModuleHandle(L"engine.dll");
	localPlayer = *(uintptr_t*)(clientModule + dwLocalPlayer);
}


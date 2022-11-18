#include "Values.h"

uintptr_t flags;
uintptr_t localPlayer;
uintptr_t clientModule;

void Values::InitInGame() {
	flags = *(uintptr_t*)(localPlayer + m_fFlags);
}

void Values::InitPreGame() {
	clientModule = (uintptr_t)GetModuleHandle(L"client.dll");
	localPlayer = *(uintptr_t*)(clientModule + dwLocalPlayer);
}


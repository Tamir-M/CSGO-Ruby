#include "AntiFlash.h"

void AntiFlash::Run() {
	if (this->isActive)
		*(uintptr_t*)(localPlayer + m_flFlashDuration) = 0;
}
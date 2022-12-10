#include "Radar.h"

void Radar::Run() {
	if (!this->isActive) return;
	for (unsigned short int i = 0; i < 64; ++i) {
		uintptr_t entity = *(uintptr_t*)(clientModule + dwEntityList + (i * 0x10));

		if (entity == NULL) break;

		*(uintptr_t*)(entity + m_bSpotted) = true;
	}
}
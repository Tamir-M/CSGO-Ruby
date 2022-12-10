#include "BHop.h"



void BHop::Run()
{
	if (this->isActive && GetAsyncKeyState(VK_SPACE) && flags & FL_ONGROUND)
		*(uintptr_t*)(clientModule + dwForceJump) = 6;
}

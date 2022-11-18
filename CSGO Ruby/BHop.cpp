#include "BHop.h"



void BHop::Run()
{
	if (GetAsyncKeyState(VK_SPACE) && flags & FL_ONGROUND)
		*(uintptr_t*)(clientModule + dwForceJump) = 6;
}

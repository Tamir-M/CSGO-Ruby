// dllmain.cpp : Defines the entry point for the DLL application.
#include "Values.h"
#include "HackFeatures.h"

#define PANIC_KEY VK_END


WORD WINAPI HackThread(HMODULE hModule) {
    Values::InitPreGame();

    while (localPlayer == NULL)
        Values::InitPreGame();
    
    InitHackFeatures();

    while (!GetAsyncKeyState(PANIC_KEY)) {
        Values::InitInGame();
        HackToggles();
        HackRuns();
        
        Sleep(1);
    }

    FreeLibraryAndExitThread(hModule, 0);
    return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH: {
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, nullptr));
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}


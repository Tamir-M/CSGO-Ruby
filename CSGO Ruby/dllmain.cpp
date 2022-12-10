// dllmain.cpp : Defines the entry point for the DLL application.
#include "Feature/HackFeatures.h"
#include "Utils/HooksD9/Hook.h"
#include "./GUI/GUI.h"

#define PANIC_KEY VK_END

void* d3d9Device[119];
BYTE EndSceneByte[7]{ 0 };
tEndScene oEndScene = nullptr;
extern LPDIRECT3DDEVICE9 pDevice = nullptr;

void APIENTRY hkEndScene(LPDIRECT3DDEVICE9 o_pDevice) {
    if (!pDevice)
        pDevice = o_pDevice;

    ESPHack->Draw();
    rCrosshairHack->Draw();

    if (!GUI::setup)
        GUI::SetupMenu(pDevice);

    if (GUI::open)
        GUI::Render();
     
    oEndScene(pDevice);
}

WORD WINAPI HackThread(HMODULE hModule) {
    Values::InitPreGame();

    while (localPlayer == NULL)
        Values::InitPreGame();

    InitHackFeatures();

    if (GetD3D9Device(d3d9Device, sizeof(d3d9Device))) {
        memcpy(EndSceneByte, (char*)d3d9Device[42], 7);

        oEndScene = (tEndScene)TrampHook((char*)d3d9Device[42], (char*)hkEndScene, 7);
    }

    while (!GetAsyncKeyState(PANIC_KEY)) {
        while (localPlayer == NULL)
            Values::InitPreGame();
        Values::InitInGame();
        HackToggles();
        HackRuns();
        
        Sleep(1);
    }

    Patch((BYTE*)d3d9Device[42], EndSceneByte, 7);
    
    Sleep(1000);

    GUI::Destroy();

    Sleep(1000);

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


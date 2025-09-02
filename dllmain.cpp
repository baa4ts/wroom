// dllmain.cpp
#include "pch.h"
#include "Hook/hook.hpp"
#include "detours/detours.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);

        originalNtQuerySystemInformation = (NtQuerySystemInformation_t)
            GetProcAddress(GetModuleHandleW(L"ntdll.dll"), "NtQuerySystemInformation");

        if (originalNtQuerySystemInformation)
        {
            DetourTransactionBegin();
            DetourUpdateThread(GetCurrentThread());
            DetourAttach((PVOID*)&originalNtQuerySystemInformation, HookNtQuerySystemInformation);
            DetourTransactionCommit();
        }
        break;

    case DLL_PROCESS_DETACH:
        if (originalNtQuerySystemInformation)
        {
            DetourTransactionBegin();
            DetourUpdateThread(GetCurrentThread());
            DetourDetach((PVOID*)&originalNtQuerySystemInformation, HookNtQuerySystemInformation);
            DetourTransactionCommit();
        }
        break;

    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
        break;
    }
    return TRUE;
}

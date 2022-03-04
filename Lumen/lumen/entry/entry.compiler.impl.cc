#include <Windows.h>
#include <indx>

#include "entry.cc"

#include <indxs>

static fun WINAPI Entry(HMODULE hModule)->int
{
    Lumen::Entry();
    FreeLibraryAndExitThread(hModule, 0);
    return 0;
}

#ifdef INDEX_Clang
__attribute__((constructor)) global fun LibraryMain()->void
{
    var hInstance = GetModuleHandle(nullptr);
    CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)Entry, hInstance, 0, nullptr);
}
#endif

#ifdef INDEX_MSVC
global fun WINAPI DllMain(HMODULE hModule, int reason, void* reserved)->bool
{
    switch (reason)
    {
    case DLL_PROCESS_ATTACH:
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)Entry, hModule, 0, nullptr));
        break;
    case DLL_PROCESS_DETACH:
        break;
    default:
        break;
    }

    return true;
}
#endif

#include <indxe>
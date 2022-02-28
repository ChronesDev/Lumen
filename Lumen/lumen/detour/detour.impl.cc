#include "detour.cc"

#include <indxs>

namespace Lumen::Detour
{
    fun InitMinHook()->void
    {
        if (MH_Initialize() != MH_OK) INDEX_THROW("MH_Initialize did not return MH_OK.");
    }

    fun DeinitMinHook()->void
    {
        if (MH_Uninitialize() != MH_OK) INDEX_THROW("MH_Uninitialize did not return MH_OK.");
    }
}

#include <indxe>
#pragma once

#include <indx>

#include "simple_detour.cc"

#include <indxs>

namespace Lumen::Detour
{
    fun InitMinHook()->void;
    fun DeinitMinHook()->void;

    typedef void (*KeyEventFunc)(ulong id, ulong value);
    global KeyEventFunc KeyEventOriginal = {};
    global SimpleDetour KeyEventDetour;

    typedef void (*MouseEventFunc)(
        UInt64 arg1, UInt64 arg2, UInt64 arg3, UInt64 arg4, UInt64 arg5, UInt64 arg6, UInt64 arg7);
    global MouseEventFunc MouseEventOriginal = {};
    global SimpleDetour MouseEventDetour;

    typedef float (*GetFovFunc)(void* that, float f, bool b);
    global GetFovFunc GetFovOriginal;
    global SimpleDetour GetFovDetour;

    typedef float (*GetGammaFunc)(void* that);
    global GetGammaFunc GetGammaOriginal;
    global SimpleDetour GetGammaDetour;

    typedef int (*GetWorldTimeFunc)(void* that);
    global GetWorldTimeFunc GetWorldTimeOriginal;
    global SimpleDetour GetWorldTimeDetour;

    typedef float (*GetMouseSensitivityFunc)(void* that, UInt64 a1);
    global GetMouseSensitivityFunc GetMouseSensitivityOriginal;
    global SimpleDetour GetMouseSensitivityDetour;
}

#include <indxe>
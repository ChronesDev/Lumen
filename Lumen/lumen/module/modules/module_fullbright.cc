#pragma once

#include <lumen/input/key.cc>
#include <lumen/module/module.cc>

#include <indxs>

fun OnGetFov(void* that, float f, bool b)->float;

namespace Lumen::Modules
{
    struct Zoom;
    extern IPtr<Zoom> ZoomModule;

    struct Fullbright : Module
    {
        Fullbright() = default;

        fun GetName() const->string override { return "Fullbright"; }
        fun GetId() const->string override { return "lumen_fullbright"; }
        fun GetDescription() const->string override { return "Fullbright makes all areas bright."; }
        fun GetHasState() const->bool override { return true; }

        fun OnInit()->void override;
        fun OnDeinit()->void override;
    };

    global IPtr<Fullbright> FullbrightModule;
}

#include <indxe>
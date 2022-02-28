#pragma once

#include <lumen/module/module.cc>

#include <indxs>

fun OnGetFov(void* that, float f, bool b)->float;

namespace Lumen::Modules
{
    struct Zoom;
    extern IPtr<Zoom> ZoomModule;

    struct Zoom : Module
    {
        fun GetName() const->string override { return "Zoom"; }
        fun GetId() const->string override { return "lumen_zoom"; }
        fun GetDescription() const->string override { return "Zooms when triggerred."; }
        fun GetHasState() const->bool override { return true; }

        fun OnInit()->void override;
        fun OnDeinit()->void override;

        fun ExecuteGet(List<string> args)->void override;
        fun ExecuteSet(List<string> args)->void override;

        float To = 30.0f;
        TimeSpan Duration = TimeSpan::FromSec(0.3);
    };

    global IPtr<Zoom> ZoomModule;
}

#include <indxe>
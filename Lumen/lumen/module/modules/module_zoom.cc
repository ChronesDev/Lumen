#pragma once

#include <lumen/module/module.cc>

#include <indxs>

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
    };

    global IPtr<Zoom> ZoomModule;
}

#include <indxe>
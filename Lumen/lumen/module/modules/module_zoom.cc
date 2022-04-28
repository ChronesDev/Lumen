#pragma once

#include <lumen/input/key.cc>
#include <lumen/module/module.cc>

#include <indxs>

fun OnGetFov(void* that, float f, bool b)->float;

namespace Lumen::Modules
{
    struct Zoom;

    struct Zoom : Module
    {
        Zoom() = default;

        fun GetName() const->string override { return "Zoom"; }
        fun GetId() const->string override { return "lumen_zoom"; }
        fun GetDescription() const->string override { return "Zooms when triggerred."; }
        fun GetHasState() const->bool override { return true; }

        fun OnInit()->void override;
        fun OnDeinit()->void override;

        fun ExecuteGet(List<string> args)->void override;
        fun ExecuteSet(List<string> args)->void override;

        fun GetHasBinding()->bool override { return true; }
        fun BindTo(Key key)->void override { BindZoom = key; }
        fun Unbind()->void override { BindZoom = Key::Null; }

        fun GetSupportsConfig() const->bool override { return true; }
        fun MakeConfig(nlohmann::json& j)->void override;
        fun LoadConfig(nlohmann::json& j)->void override;

        bool IsZooming = false;

        float To = 40.0f;
        TimeSpan Duration = TimeSpan::FromSec(0.1);

        Key BindZoom = Key::Null;
        bool IsZoomKeyPressed = false;

        float ZoomProgress = 0;
        TimePoint ZoomProcessPoint = Time.Now;

        IPtr<IEasing> Easing = INew<QuartOutEasing>();
        string EasingName = "QuartOut";

        float InFactor = 1;
        float OutFactor = 1;

        Nullable<float> SensitivityTo = Null;

        float HandFov = 0;
    };

    global IPtr<Zoom> ZoomModule;
}

#include <indxe>
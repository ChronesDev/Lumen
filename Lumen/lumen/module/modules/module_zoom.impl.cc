#include "module_zoom.cc"

#include <lumen/detour/detour.cc>
#include <lumen/input/input.cc>
#include <lumen/log/log.cc>
#include <lumen/signature/signature.cc>

#include <indxs>

static fun OnGetFov_(void* that, float f, bool b)->float;
static fun OnKeyEvent_(Lumen::Key key, Lumen::KeyState state, bool& handled, bool& cancel)->void;
static fun OnGetMouseSensitivity_(void* that, UInt64 a1)->float;

static List<std::pair<string, IPtr<IEasing>>> Easings_ = {
    { "Linear", INew<LinearEasing>() },

    { "QuartOut", INew<QuartOutEasing>() },
    { "QuartInOut", INew<QuartInOutEasing>() },

    { "CubicOut", INew<CubicOutEasing>() },
    { "CubicInOut", INew<CubicInOutEasing>() },

    { "CircOut", INew<CircOutEasing>() },
    { "CircInOut", INew<CircInOutEasing>() },

    { "SizeOut", INew<SineOutEasing>() },
    { "SizeInOut", INew<SineInOutEasing>() },
};

namespace Lumen::Modules
{
    fun Zoom::OnInit()->void
    {
        if (!ZoomModule.IsNull) INDEX_THROW("Duplicate of " + Name + " found.");
        ZoomModule = ISelf().DynamicAs<Zoom>();

        Input::KeyEvent += OnKeyEvent_;
        Log("(Zoom) Registered to KeyEvent");

        var result1 = Mem.FindSignature(Signature::GetFov);
        Detour::GetFovDetour.Hook(result1, Detour::GetFovOriginal, OnGetFov_);
        Log("(Zoom) Hooked GetFovDetour");

        var result2 = Mem.FindSignature(Signature::GetMouseSensitivity);
        Detour::GetMouseSensitivityDetour.Hook(result2, Detour::GetMouseSensitivityOriginal, OnGetMouseSensitivity_);
        Log("(Zoom) Hooked GetMouseSensitivityDetour");
    }

    fun Zoom::OnDeinit()->void
    {
        var self = ISelf();
        ZoomModule = nullptr;

        Input::KeyEvent -= OnKeyEvent_;
        Log("(Zoom) Unregistered from KeyEvent");
    }

    fun Zoom::ExecuteGet(List<string> args)->void
    {
        using namespace rang;

        if (args.Length > 0)
        {
            if (args[0] == "to")
            {
                if (args.Length != 1)
                {
                    Log.Fail("Wrong amount of arguments.");
                    Log.Custom(fgB::green, "... to", "\t\t", fg::blue, "");
                    return;
                }
                Log.Custom(fgB::blue, "-> ", To);
            }

            elif (args[0] == "duration" || args[0] == "dur")
            {
                if (args.Length != 1)
                {
                    Log.Fail("Wrong amount of arguments.");
                    Log.Custom(fgB::green, "... duration", "\t\t", fg::blue, "");
                    return;
                }
                Log.Custom(fgB::blue, "-> ", Duration.Sec);
            }

            elif (args[0] == "easing" || args[0] == "ease")
            {
                if (args.Length != 1)
                {
                    Log.Fail("Wrong amount of arguments.");
                    Log.Custom(fgB::green, "... easing", "\t\t", fg::blue, "");
                    return;
                }

                Log.Custom(fgB::blue, "-> ", EasingName);
            }

            elif (args[0] == "infactor" || args[0] == "infac")
            {
                if (args.Length != 1)
                {
                    Log.Fail("Wrong amount of arguments.");
                    Log.Custom(fgB::green, "... infactor", "\t\t", fg::blue, "");
                    return;
                }

                try
                {
                    InFactor = (float)std::stod(args[1]);
                }
                catch (...)
                {
                    Log.Fail("Wrong argument.");
                }
                Log.Custom(fgB::blue, "-> ", InFactor);
            }

            elif (args[0] == "outfactor" || args[0] == "outfac")
            {
                if (args.Length != 1)
                {
                    Log.Fail("Wrong amount of arguments.");
                    Log.Custom(fgB::green, "... outfactor", "\t\t", fg::blue, "");
                    return;
                }

                try
                {
                    OutFactor = (float)std::stod(args[1]);
                }
                catch (...)
                {
                    Log.Fail("Wrong argument.");
                }
                Log.Custom(fgB::blue, "-> ", OutFactor);
            }

            elif (args[0] == "sensitivity")
            {
                if (args.Length != 1)
                {
                    Log.Fail("Wrong amount of arguments.");
                    Log.Custom(fgB::green, "... sensitivity", "\t\t", fg::blue, "");
                    return;
                }
                Log.Custom(
                    fgB::blue, "-> ", SensitivityTo.HasValue ? std::to_string(SensitivityTo.Value) : (string) "none");
            }

            elif (args[0] == "hand")
            {
                if (args.Length != 1)
                {
                    Log.Fail("Wrong amount of arguments.");
                    Log.Custom(fgB::green, "... to", "\t\t", fg::blue, "");
                    return;
                }
                Log.Custom(fgB::blue, "-> ", HandFov != 0 ? std::to_string(HandFov) : "none");
            }
        }
    }

    fun Zoom::ExecuteSet(List<string> args)->void
    {
        using namespace rang;

        if (args.Length > 0)
        {
            if (args[0] == "to")
            {
                if (args.Length != 2)
                {
                    Log.Fail("Wrong amount of arguments.");
                    Log.Custom(fgB::green, "... to (value)", "\t\t", fg::blue, "");
                    return;
                }
                try
                {
                    To = (float)std::stod(args[1]);
                }
                catch (...)
                {
                    Log.Fail("Wrong argument.");
                }
                Log.Custom(fgB::blue, "-> ", To);
            }

            elif (args[0] == "duration" || args[0] == "dur")
            {
                if (args.Length != 2)
                {
                    Log.Fail("Wrong amount of arguments.");
                    Log.Custom(fgB::green, "... duration (value)", "\t\t", fg::blue, "");
                    return;
                }
                try
                {
                    Duration = TimeSpan::FromSec(std::stod(args[1]));
                }
                catch (...)
                {
                    Log.Fail("Wrong argument.");
                }
                Log.Custom(fgB::blue, "-> ", Duration.Sec);
            }

            elif (args[0] == "easing" || args[0] == "ease")
            {
                if (args.Length != 2)
                {
                    Log.Fail("Wrong amount of arguments.");
                    Log.Custom(fgB::green, "... duration (value)", "\t\t", fg::blue, "");
                    return;
                }

                if (args[1] == "list")
                {
                    string all = "";
                    for (var& e : Easings_)
                    {
                        all += e.first + ", ";
                    }
                    Log.Custom(fg::blue, "All available easing functions: ", fgB::blue,
                        all.SubString(0, Max<ulong>(all.Length - 2, 0)));
                    return;
                }

                try
                {
                    for (var& e : Easings_)
                    {
                        if (e.first.ToLower() == args[1].ToLower())
                        {
                            Easing = e.second;
                            EasingName = e.first;
                            goto jmp_finish;
                        }
                    }
                    Log.Fail(args[0], " does not exist. Use ", fg::yellow, "set zoom ease list", fgB::red,
                        " to list them all.");
                    return;
                }
                catch (...)
                {
                    Log.Fail("Wrong argument.");
                }
            jmp_finish:
                Log.Custom(fgB::blue, "-> ", EasingName);
            }

            elif (args[0] == "infactor" || args[0] == "infac")
            {
                if (args.Length != 2)
                {
                    Log.Fail("Wrong amount of arguments.");
                    Log.Custom(fgB::green, "... infactor (value)", "\t\t", fg::blue, "");
                    return;
                }
                try
                {
                    InFactor = (float)std::stod(args[1]);
                }
                catch (...)
                {
                    Log.Fail("Wrong argument.");
                }
                Log.Custom(fgB::blue, "-> ", InFactor);
            }

            elif (args[0] == "outfactor" || args[0] == "outfac")
            {
                if (args.Length != 2)
                {
                    Log.Fail("Wrong amount of arguments.");
                    Log.Custom(fgB::green, "... outfactor (value)", "\t\t", fg::blue, "");
                    return;
                }
                try
                {
                    OutFactor = (float)std::stod(args[1]);
                }
                catch (...)
                {
                    Log.Fail("Wrong argument.");
                }
                Log.Custom(fgB::blue, "-> ", OutFactor);
            }

            elif (args[0] == "sensitivity")
            {
                if (args.Length != 2)
                {
                    Log.Fail("Wrong amount of arguments.");
                    Log.Custom(fgB::green, "... sensitivity (value/\"none\")", "\t\t", fg::blue, "");
                    return;
                }
                try
                {
                    if (args[1] == "none") SensitivityTo = Null;
                    else
                        SensitivityTo = Limit<float>((float)std::stod(args[1]), 0, 2);
                }
                catch (...)
                {
                    Log.Fail("Wrong argument.");
                }
                Log.Custom(fgB::blue, "-> ", SensitivityTo.HasValue ? std::to_string(SensitivityTo.Value) : "none");
            }

            elif (args[0] == "hand")
            {
                if (args.Length != 2)
                {
                    Log.Fail("Wrong amount of arguments.");
                    Log.Custom(fgB::green, "... hand (value)", "\t\t", fg::blue, "");
                    return;
                }
                try
                {
                    if (args[1] == "none")
                    {
                        HandFov = 0;
                    }
                    else
                    {
                        HandFov = (float)std::stod(args[1]);
                    }
                }
                catch (...)
                {
                    Log.Fail("Wrong argument.");
                }
                Log.Custom(fgB::blue, "-> ", HandFov != 0 ? std::to_string(HandFov) : "none");
            }
        }
    }

    fun Zoom::MakeConfig(nlohmann::json& j)->void
    {
        j["IsEnabled"] = IsEnabled;
        j["To"] = To;
        j["Duration"] = Duration.Sec;
        j["BindZoom"] = Input::KeyToKeyName(BindZoom);
        j["Easing"] = EasingName;
        j["InFactor"] = InFactor;
        j["OutFactor"] = OutFactor;
        j["SensitivityTo"] = Limit<float>(SensitivityTo.ValueOr(0), 0, 2);
        j["HandFov"] = HandFov;
    }
    fun Zoom::LoadConfig(nlohmann::json& j)->void
    {
        SetState(j["IsEnabled"]);
        To = j.value("To", 40.f);
        Duration = TimeSpan::FromSec(j.value("Duration", 0.1));
        BindZoom = Input::FindKeyByKeyName((std::string)j["BindZoom"]);
        InFactor = j.value("InFactor", 1);
        OutFactor = j.value("OutFactor", 1);

        SensitivityTo = Limit<float>(j["SensitivityTo"], 0, 2);
        if (SensitivityTo.Value == 0) SensitivityTo = Null;

        HandFov = j.value("HandFov", 0);

        // Easing
        {
            string easing = (std::string)j["Easing"];
            for (var& e : Easings_)
            {
                if (e.first.ToLower() == easing.ToLower())
                {
                    Easing = e.second;
                    EasingName = e.first;
                    break;
                }
            }
        }
    }
}

static fun OnGetFov_(void* that, float f, bool b)->float
{
    using namespace Lumen;
    using namespace Lumen::Modules;

    if (ZoomModule.IsNull) INDEX_THROW("ZoomModule was null.");

    var now = Time.Now;
    var fov = Detour::GetFovOriginal(that, f, b);

    if (b)
    {
        if (ZoomModule->IsDisabled) return fov;

        if (ZoomModule->IsZooming)
        {
            var duration = (float)ZoomModule->Duration.Sec;
            var& processPoint = ZoomModule->ZoomProcessPoint;
            var& progress = ZoomModule->ZoomProgress;
            var& to = ZoomModule->To;

            if (ZoomModule->IsZoomKeyPressed)
            {
                if (duration == 0) return to;

                var lasted = (now - processPoint).Sec;
                var frac = (float)(lasted / duration) * ZoomModule->InFactor;
                progress = Clamp<float>(progress + frac, 0, 1);
            }

            else
            {
                if (duration == 0) return to;

                var lasted = (now - processPoint).Sec;
                var frac = (float)(lasted / duration) * ZoomModule->OutFactor;
                progress = Clamp<float>(progress - frac, 0, 1);
            }

            processPoint = now;
            return Lerp<float>(fov, to, (float)ZoomModule->Easing->operator()(progress));
        }
    }
    else
    {
        if (ZoomModule->HandFov != 0)
        {
            return ZoomModule->HandFov;
        }
    }

    return fov;
}

static fun OnKeyEvent_(Lumen::Key key, Lumen::KeyState state, bool& handled, bool& cancel)->void
{
    using namespace Lumen;
    using namespace Lumen::Modules;

    if (ZoomModule.IsNull) INDEX_THROW("ZoomModule was null.");
    if (ZoomModule->IsDisabled) return;

    if (key != ZoomModule->BindZoom) return;

    if (state == KeyState::Pressed)
    {
        ZoomModule->IsZooming = true;
        ZoomModule->IsZoomKeyPressed = true;
    }

    if (state == KeyState::Released)
    {
        ZoomModule->IsZooming = true;
        ZoomModule->IsZoomKeyPressed = false;
    }

    handled = true;
}

static fun OnGetMouseSensitivity_(void* that, UInt64 a1)->float
{
    using namespace Lumen;
    using namespace Lumen::Modules;

    if (ZoomModule.IsNull) INDEX_THROW("ZoomModule was null.");
    if (ZoomModule->IsDisabled) return Detour::GetMouseSensitivityOriginal(that, a1);

    var sens = Detour::GetMouseSensitivityOriginal(that, a1);
    if (!ZoomModule->SensitivityTo.HasValue) return sens;

    if (ZoomModule->IsZooming)
    {
        var& progress = ZoomModule->ZoomProgress;
        var to = ZoomModule->SensitivityTo.Value;

        return Lerp<float>(sens, to, (float)ZoomModule->Easing->operator()(progress));
    }
    else
        return sens;
}

#include <indxe>
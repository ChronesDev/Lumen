#include "module_zoom.cc"

#include <lumen/detour/detour.cc>
#include <lumen/input/input.cc>
#include <lumen/log/log.cc>
#include <lumen/signature/signature.cc>

#include <indxs>

fun OnGetFov_(void* that, float f, bool b)->float;
fun OnKeyEvent_(Lumen::Key key, Lumen::KeyState state, bool& handled, bool& cancel)->void;

namespace Lumen::Modules
{
    fun Zoom::OnInit()->void
    {
        if (!ZoomModule.IsNull) INDEX_THROW("Duplicate of " + Name + " found.");
        ZoomModule = ISelf().DynamicAs<Zoom>();

        Input::KeyEvent += OnKeyEvent_;
        Log("(Zoom) Registered to KeyEvent");

        var result = Mem.FindSignature(Signature::GetFov);
        Detour::GetFovDetour.Hook(result, Detour::GetFovOriginal, OnGetFov_);
        Log("(Zoom) Hooked GetFovDetour");
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

            elif (args[0] == "duration")
            {
                if (args.Length != 1)
                {
                    Log.Fail("Wrong amount of arguments.");
                    Log.Custom(fgB::green, "... duration", "\t\t", fg::blue, "");
                    return;
                }
                Log.Custom(fgB::blue, "-> ", Duration.Sec);
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

            elif (args[0] == "duration")
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
        }
    }
}

fun OnGetFov_(void* that, float f, bool b)->float
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
            var keyHitPoint = ZoomModule->ZoomKeyPoint;
            var duration = ZoomModule->Duration.Sec;
            var to = ZoomModule->To;

            if (ZoomModule->IsZoomKeyPressed)
            {
                var lasted = (now - keyHitPoint).Sec;

                if (duration == 0) return to;

                var frac = Clamp<float>((float)(lasted / duration), 0, 1);
                //if (frac == 1) ZoomModule->IsZooming = false;

                ZoomModule->ZoomProgress = frac;
                return (to - fov) * frac + fov;
            }

            else
            {
                var lasted = (now - keyHitPoint).Sec;

                if (duration == 0) return fov;

                var frac = ZoomModule->ZoomProgress - Clamp<float>((float)(lasted / duration), 0, 1);
                if (frac <= 0) ZoomModule->IsZooming = false;

                return (to - fov) * frac + fov;
            }
        }
    }

    return fov;
}

fun OnKeyEvent_(Lumen::Key key, Lumen::KeyState state, bool& handled, bool& cancel)->void
{
    using namespace Lumen;
    using namespace Lumen::Modules;

    if (ZoomModule.IsNull) INDEX_THROW("ZoomModule was null.");
    if (ZoomModule->IsDisabled) return;

    var now = Time.Now;
    if (key != Key::Null && key == ZoomModule->BindZoom)
    {
        if (state == KeyState::Pressed)
        {
            ZoomModule->IsZooming = true;
            ZoomModule->IsZoomKeyPressed = true;
            ZoomModule->ZoomKeyPoint = now;
        }

        if (state == KeyState::Released)
        {
            ZoomModule->IsZooming = true;
            ZoomModule->IsZoomKeyPressed = false;
            ZoomModule->ZoomKeyPoint = now;
        }

        handled = true;
    }
}

#include <indxe>
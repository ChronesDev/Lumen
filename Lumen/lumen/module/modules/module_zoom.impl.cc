#include "module_zoom.cc"

#include <lumen/detour/detour.cc>
#include <lumen/log/log.cc>

#include <indxs>

fun OnGetFov_(void* that, float f, bool b)->float;

namespace Lumen::Modules
{
    fun Zoom::OnInit()->void
    {
        if (!ZoomModule.IsNull) INDEX_THROW("Duplicate of " + Name + " found.");
        ZoomModule = ISelf().DynamicAs<Zoom>();
    }

    fun Zoom::OnDeinit()->void
    {
        var self = ISelf();
        ZoomModule = nullptr;
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

    var fov = Detour::GetFovOriginal(that, f, b);

    if (b)
    {
        // TODO: Make this
    }

    return fov;
}

#include <indxe>
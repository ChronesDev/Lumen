#include "module_timechanger.cc"

#include <lumen/detour/detour.cc>
#include <lumen/input/input.cc>
#include <lumen/log/log.cc>
#include <lumen/signature/signature.cc>

#include <indxs>

static fun OnGetWorldTime_(void* that)->int;

namespace Lumen::Modules
{
    fun TimeChanger::OnInit()->void
    {
        if (!TimeChangerModule.IsNull) INDEX_THROW("Duplicate of " + Name + " found.");
        TimeChangerModule = ISelf().DynamicAs<TimeChanger>();

        var result = Mem.FindSignature(Signature::GetWorldTime);
        Detour::GetWorldTimeDetour.Hook(result, Detour::GetWorldTimeOriginal, OnGetWorldTime_);
        Log("(TimeChanger) Hooked GetWorldTime");
    }

    fun TimeChanger::OnDeinit()->void
    {
        var self = ISelf();
        TimeChangerModule = nullptr;
    }

    fun TimeChanger::OnEnable()->void { Enabled.Invoke(); }
    fun TimeChanger::OnDisable()->void { Disabled.Invoke(); }

    fun TimeChanger::ExecuteGet(List<string> args)->void
    {
        using namespace rang;

        if (args.Length > 0)
        {
            if (args[0] == "time")
            {
                if (args.Length != 1)
                {
                    Log.Fail("Wrong amount of arguments.");
                    Log.Custom(fgB::green, "... to", "\t\t", fg::blue, "");
                    return;
                }
                Log.Custom(fgB::blue, "-> ", CustomTime);
            }
        }
    }

    fun TimeChanger::ExecuteSet(List<string> args)->void
    {
        using namespace rang;

        if (args.Length > 0)
        {
            if (args[0] == "time")
            {
                if (args.Length != 2)
                {
                    Log.Fail("Wrong amount of arguments.");
                    Log.Custom(fgB::green, "... to (value)", "\t\t", fg::blue, "");
                    return;
                }
                try
                {
                    CustomTime = (float)std::stoi(args[1]);
                }
                catch (...)
                {
                    Log.Fail("Wrong argument.");
                }
                Log.Custom(fgB::blue, "-> ", CustomTime);
            }
        }
    }

    fun TimeChanger::MakeConfig(nlohmann::json& j)->void
    {
        j["IsEnabled"] = IsEnabled;
        j["CustomTime"] = CustomTime_;
    }
    fun TimeChanger::LoadConfig(nlohmann::json& j)->void
    {
        SetState(j["IsEnabled"]);
        CustomTime_ = j["CustomTime"];
    }
}

static fun OnGetWorldTime_(void* that)->int
{
    using namespace Lumen;
    using namespace Lumen::Modules;

    if (TimeChangerModule.IsNull) INDEX_THROW("TimeChangerModule was null.");

    var time = Detour::GetWorldTimeOriginal(that);
    if (TimeChangerModule->IsDisabled) return time;

    return TimeChangerModule->CustomTime;
}

#include <indxe>
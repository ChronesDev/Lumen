#include "module_night.cc"

#include "module_timechanger.cc"

#include <lumen/log/log.cc>

#include <indxs>

fun OnTimeChangerDisabled_()->void;
fun OnTimeChangerCustomTimeChanged_()->void;

namespace Lumen::Modules
{
    fun Night::OnInit()->void
    {
        if (!NightModule.IsNull) INDEX_THROW("Duplicate of " + Name + " found.");
        NightModule = ISelf().DynamicAs<Night>();
    }

    fun Night::OnDeinit()->void
    {
        var self = ISelf();
        NightModule = nullptr;
    }

    fun Night::OnEnable()->void
    {
        TimeChangerModule->CustomTime = 42000;
        if (TimeChangerModule->IsDisabled) TimeChangerModule->Enable();

        if (!TimeChangerModule->Disabled.Contains(OnTimeChangerDisabled_))
            TimeChangerModule->Disabled += OnTimeChangerDisabled_;

        if (!TimeChangerModule->CustomTimeChanged.Contains(OnTimeChangerCustomTimeChanged_))
            TimeChangerModule->CustomTimeChanged += OnTimeChangerCustomTimeChanged_;
    }

    fun Night::OnDisable()->void
    {
        if (TimeChangerModule->IsEnabled) TimeChangerModule->Disable();
    }
}

fun OnTimeChangerDisabled_()->void
{
    using namespace Lumen;
    using namespace Lumen::Modules;

    if (NightModule.IsNull) INDEX_THROW("NightModule was null.");

    NightModule->Disable();
}

fun OnTimeChangerCustomTimeChanged_()->void
{
    using namespace Lumen;
    using namespace Lumen::Modules;

    if (NightModule.IsNull) INDEX_THROW("NightModule was null.");
    if (NightModule->IsDisabled) return;

    if (TimeChangerModule->CustomTime != Night::NightTime)
    {
        NightModule->Disable();
    }
}

#include <indxe>
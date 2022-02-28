#include "module.cc"

#include <indxs>

namespace Lumen
{
    fun Module::Init()->void
    {
        OnInit();
    }

    fun Module::Deinit()->void
    {
        OnDeinit();

        if (IsEnabled && HasState) Disable();
    }

    fun Module::Enable()->void
    {
        if (IsEnabled) INDEX_THROW("Already enabled.");

        OnEnable();
    }

    fun Module::Disable()->void
    {
        if (IsDisabled) INDEX_THROW("Already disabled.");

        OnDisable();
    }
}

#include <indxe>
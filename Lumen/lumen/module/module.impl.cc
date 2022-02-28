#include "module.cc"

#include <lumen/log/log.cc>

#include <indxs>

namespace Lumen
{
    Module::~Module()
    {
        if (Initialized_) Deinit();
    }

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
        Enabled_ = true;

        try
        {
            OnEnable();
        }
        catch (std::exception& ex)
        {
            Enabled_ = false;
            throw ex;
        }
    }

    fun Module::Disable()->void
    {
        if (IsDisabled) INDEX_THROW("Already disabled.");
        Enabled_ = false;

        try
        {
            OnDisable();
        }
        catch (std::exception& ex)
        {
            Enabled_ = true;
            throw ex;
        }
    }

    fun Module::ExecuteGet(List<string> args)->void
    {
        Log.Custom("This module doesn't have any gettable properties.");
    }
    fun Module::ExecuteSet(List<string> args)->void
    {
        Log.Custom("This module doesn't have any settable properties.");
    }
}

#include <indxe>
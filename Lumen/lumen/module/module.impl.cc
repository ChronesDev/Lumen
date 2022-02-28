#include "module.cc"

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
        OnDisable();

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
}

#include <indxe>
#include "dx11on12.cc"

#include <indxs>

namespace Lumen::Render::DX11On12
{
    static bool Initialized_ = false;
    fun IsInitialized()->bool { return Initialized_; }

    fun Init()->void
    {
        if (Initialized_) INDEX_THROW("Already initialized.");

        Initialized_ = true;
    }

    fun Deinit()->void
    {
        if (!Initialized_) INDEX_THROW("Already deinitialized.");

        Initialized_ = false;
    }
}

#include <indxe>
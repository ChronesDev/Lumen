#include "dx11on12.cc"

#include "dx11on12.d3d12.cc"
#include "dx11on12.dxgi.cc"

#include <indxs>

namespace Lumen::Render::DX11On12
{
    static bool Initialized_ = false;
    fun HasInit()->bool { return Initialized_; }

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
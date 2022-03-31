#include "render.cc"

#include <indxs>

namespace Lumen::Render
{
    static bool Initialized_ = false;
    fun HasInit()->bool { return Initialized_; }

    static RenderType RenderType_ = {};

    fun Init(RenderType type)->void
    {
        if (Initialized_) INDEX_THROW("Already initialized.");

        RenderType_ = type;
        switch (RenderType_)
        {
        case RenderType::D2D:
            D2D::Init();
            break;
        default:
            INDEX_THROW("Unsupported RenderType.");
        }

        Initialized_ = true;
    }

    fun Deinit()->void
    {
        if (!Initialized_) INDEX_THROW("Already deinitialized.");

        switch (RenderType_)
        {
        case RenderType::D2D:
            D2D::Deinit();
            break;
        default:
            INDEX_THROW("Unknown RenderType.");
        }

        Initialized_ = false;
    }

    fun TryDeinit()->void
    {
        if (Initialized_) Deinit();
    }
}

#include <indxe>
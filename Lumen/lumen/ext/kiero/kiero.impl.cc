#include "kiero.cc"

#include <indxs>

namespace Lumen::Ext::Kiero
{
    static bool Initialized_ = false;
    [[maybe_unused]] fun HasInit()->bool { return Initialized_; }

    fun Init(kiero::RenderType::Enum renderType)->void
    {
        if (Initialized_) INDEX_THROW("Already initialized.");

        var result = kiero::init(renderType);
        switch (result)
        {
        case kiero::Status::Success:
        case kiero::Status::AlreadyInitializedError:
            if (kiero::getRenderType() == renderType) break;
            INDEX_THROW("kiero::init returned AlreadyInitializedError.");
        case kiero::Status::NotInitializedError:
            INDEX_THROW("kiero::init returned NotInitializedError.");
        case kiero::Status::NotSupportedError:
            INDEX_THROW("kiero::init returned NotSupportedError.");
        case kiero::Status::ModuleNotFoundError:
            INDEX_THROW("kiero::init returned ModuleNotFoundError.");
        case kiero::Status::UnknownError:
            INDEX_THROW("kiero::init returned an unknown error.");
        default:
            INDEX_THROW("kiero::init returned an unknown return value.");
        }

        var result2 = kiero::init_IDXGISwapchain1_Bindings_();
        switch (result2)
        {
        case kiero::Status::Success:
        case kiero::Status::AlreadyInitializedError:
            if (kiero::getRenderType() == renderType) break;
            INDEX_THROW("kiero::init_IDXGISwapchain1_Bindings_ returned AlreadyInitializedError.");
        case kiero::Status::NotInitializedError:
            INDEX_THROW("kiero::init_IDXGISwapchain1_Bindings_ returned NotInitializedError.");
        case kiero::Status::NotSupportedError:
            INDEX_THROW("kiero::init_IDXGISwapchain1_Bindings_ returned NotSupportedError.");
        case kiero::Status::ModuleNotFoundError:
            INDEX_THROW("kiero::init_IDXGISwapchain1_Bindings_ returned ModuleNotFoundError.");
        case kiero::Status::UnknownError:
            INDEX_THROW("kiero::init_IDXGISwapchain1_Bindings_ returned an unknown error.");
        default:
            INDEX_THROW("kiero::init_IDXGISwapchain1_Bindings_ returned an unknown return value.");
        }

        Initialized_ = true;
    }
    fun Deinit()->void
    {
        if (!Initialized_) INDEX_THROW("Already deinitialized.");

        kiero::shutdown_IDXGISwapchain1_Bindings_();
        kiero::shutdown();

        Initialized_ = false;
    }
}

#include <indxe>
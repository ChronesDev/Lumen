#include <lumen/ext/kiero/kiero.cc>

#include "d2d.dxgi.cc"

#include <indxs>

namespace Lumen::Render::D2D
{
    static bool IsDXGIPresentHooked_ = false;
    static bool IsDXGIResizeBuffersHooked_ = false;
    static bool IsDXGIReleaseHooked_ = false;

    [[maybe_unused]] fun IsDXGIPresentHooked()->bool { return IsDXGIPresentHooked_; }
    [[maybe_unused]] fun IsDXGIResizeBuffersHooked()->bool { return IsDXGIResizeBuffersHooked_; }
    [[maybe_unused]] fun IsDXGIReleaseHooked()->bool { return IsDXGIReleaseHooked_; }

    fun HookDXGIPresent(DXGIPresentFunc f)->void
    {
        if (f == nullptr) INDEX_THROW("f was nullptr.");
        if (IsDXGIPresentHooked_) INDEX_THROW("Already hooked.");

        if (!Ext::Kiero::HasInit()) INDEX_THROW("Kiero hasn't been initialized yet.");

        if (kiero::bind(140, (void**)&DXGIPresentOriginal, (void*)f) != kiero::Status::Success)
            INDEX_THROW("kiero::bind failed (DXGIPresentOriginal).");

        IsDXGIPresentHooked_ = true;
    }
    fun UnhookDXGIPresent()->void
    {
        if (!IsDXGIPresentHooked_) INDEX_THROW("Already unhooked.");

        if (!Ext::Kiero::HasInit()) return;

        kiero::unbind_MH_RemoveHook(140);

        IsDXGIPresentHooked_ = false;
    }

    fun HookDXGIResizeBuffers(DXGIResizeBuffersFunc f)->void
    {
        if (f == nullptr) INDEX_THROW("f was nullptr.");
        if (IsDXGIResizeBuffersHooked_) INDEX_THROW("Already hooked.");

        if (!Ext::Kiero::HasInit()) INDEX_THROW("Kiero hasn't been initialized yet.");

        if (kiero::bind(145, (void**)&DXGIResizeBuffersOriginal, (void*)f) != kiero::Status::Success)
            INDEX_THROW("kiero::bind failed (DXGIResizeBuffersOriginal).");

        IsDXGIResizeBuffersHooked_ = true;
    }
    fun UnhookDXGIResizeBuffers()->void
    {
        if (!IsDXGIResizeBuffersHooked_) INDEX_THROW("Already unhooked.");

        if (!Ext::Kiero::HasInit()) return;

        kiero::unbind_MH_RemoveHook(145);

        IsDXGIResizeBuffersHooked_ = false;
    }

    fun HookDXGIRelease(DXGIReleaseFunc f)->void
    {
        if (f == nullptr) INDEX_THROW("f was nullptr.");
        if (IsDXGIReleaseHooked_) INDEX_THROW("Already hooked.");

        if (!Ext::Kiero::HasInit()) INDEX_THROW("Kiero hasn't been initialized yet.");

        if (kiero::bind(134, (void**)&DXGIReleaseOriginal, (void*)f) != kiero::Status::Success)
            INDEX_THROW("kiero::bind failed (DXGIReleaseOriginal).");

        IsDXGIReleaseHooked_ = true;
    }
    fun UnhookDXGIRelease()->void
    {
        if (!IsDXGIReleaseHooked_) INDEX_THROW("Already unhooked.");

        if (!Ext::Kiero::HasInit()) return;

        kiero::unbind_MH_RemoveHook(134);

        IsDXGIReleaseHooked_ = false;
    }
}

#include <indxe>
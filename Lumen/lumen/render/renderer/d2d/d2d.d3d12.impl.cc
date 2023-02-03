#include <lumen/ext/kiero/kiero.cc>

#include "d2d.d3d12.cc"

#include <indxs>

namespace Lumen::Render::D2D
{
    static bool IsIsD3D12ExecuteCommandListsHooked_ = false;
    [[maybe_unused]] fun IsD3D12ExecuteCommandListsHooked()->bool { return IsIsD3D12ExecuteCommandListsHooked_; }

    fun HookD3D12ExecuteCommandLists(D3D12ExecuteCommandListsFunc f)->void
    {
        if (f == nullptr) INDEX_THROW("f was nullptr.");
        if (IsIsD3D12ExecuteCommandListsHooked_) INDEX_THROW("Already hooked.");

        if (!Ext::Kiero::HasInit()) INDEX_THROW("Kiero hasn't been initialized yet.");

        if (kiero::bind(54, (void**)&D3D12ExecuteCommandListsOriginal, (void*)f) != kiero::Status::Success)
            INDEX_THROW("kiero::bind failed (D3D12ExecuteCommandListsOriginal).");

        IsIsD3D12ExecuteCommandListsHooked_ = true;
    }
    fun UnhookD3D12ExecuteCommandLists()->void
    {
        if (!IsIsD3D12ExecuteCommandListsHooked_) INDEX_THROW("Already unhooked.");

        if (!Ext::Kiero::HasInit()) return;

        kiero::unbind_MH_RemoveHook(54);

        IsIsD3D12ExecuteCommandListsHooked_ = false;
    }
}

#include <indxe>
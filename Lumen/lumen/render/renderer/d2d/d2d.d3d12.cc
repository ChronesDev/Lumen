#pragma once

#include <lumen/ext/dx/dx.cc>

#include <indx>

#include <indxs>

namespace Lumen::Render::D2D
{
    typedef void (*D3D12ExecuteCommandListsFunc)(
        ID3D12CommandQueue* CommandQueuePtr, uint CommandListsCount, ID3D12CommandList* CommandListPtr);

    global D3D12ExecuteCommandListsFunc D3D12ExecuteCommandListsOriginal = {};

    [[maybe_unused]] fun IsD3D12ExecuteCommandListsHooked()->bool;

    fun HookD3D12ExecuteCommandLists(D3D12ExecuteCommandListsFunc f)->void;
    fun UnhookD3D12ExecuteCommandLists()->void;
}

#include <indxe>
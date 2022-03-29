#pragma once

#include <d3d12.h>

#include "dx11on12.cc"

#include <indxs>

namespace Lumen::Render::DX11On12
{
    typedef void (*D3D12ExecuteCommandListsFunc)(
        ID3D12CommandQueue* CommandQueuePtr, uint CommandListsCount, ID3D12CommandList* CommandListPtr);

    global D3D12ExecuteCommandListsFunc D3D12ExecuteCommandListsOriginal = {};

    [[maybe_unused]] fun IsD3D12ExecuteCommandListsHooked()->bool;

    fun HookD3D12ExecuteCommandLists(D3D12ExecuteCommandListsFunc f)->void;
    fun UnhookD3D12ExecuteCommandLists()->void;
}

#include <indxe>
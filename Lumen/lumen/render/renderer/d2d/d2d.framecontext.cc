#pragma once

#include <d3d12.h>

#include <indxs>

namespace Lumen::Render::D2D
{
    struct FrameContext
    {
        ID3D12CommandAllocator* CommandAllocatorPtr = nullptr;
        ID3D12Resource* MainRenderTargetResourcePtr = nullptr;
        D3D12_CPU_DESCRIPTOR_HANDLE MainRenderTargetDescriptor {};
    };
}

#include <indxe>
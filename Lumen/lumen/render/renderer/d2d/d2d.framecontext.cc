#pragma once

#include <winrt/base.h>
#include <lumen/ext/dx/dx.cc>

#include <indxs>

namespace Lumen::Render::D2D
{
    struct FrameContext
    {
        winrt::com_ptr<ID3D12CommandAllocator> CommandAllocator = nullptr;
        winrt::com_ptr<ID3D12Resource> MainRenderTargetResource = nullptr;
        D3D12_CPU_DESCRIPTOR_HANDLE MainRenderTargetDescriptor {};
    };
}

#include <indxe>
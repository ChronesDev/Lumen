#pragma once

#include <dxgi1_6.h>
#include <indx>

#include <indxs>

namespace Lumen::Render::DX11On12
{
    typedef long(__fastcall* DXGIPresentFunc)(IDXGISwapChain3* SwapChainPtr, uint SyncInterval, uint Flags);
    typedef HRESULT(__fastcall* DXGIResizeBuffersFunc)(IDXGISwapChain* SwapChainPtr, uint BufferCount, uint Width,
        uint Height, DXGI_FORMAT NewFormat, uint SwapChainFlags);

    global DXGIPresentFunc DXGIPresentOriginal = {};
    global DXGIResizeBuffersFunc DXGIResizeBuffersOriginal = {};

    [[maybe_unused]] fun IsDXGIPresentHooked()->bool;
    [[maybe_unused]] fun IsDXGIResizeBuffersHooked()->bool;

    fun HookDXGIPresent(DXGIPresentFunc f)->void;
    fun UnhookDXGIPresent()->void;

    fun HookDXGIResizeBuffers(DXGIResizeBuffersFunc f)->void;
    fun UnhookDXGIResizeBuffers()->void;
}

#include <indxe>
#pragma once

#include <lumen/ext/dx/dx.cc>

#include <indx>

#include <indxs>

namespace Lumen::Render::D2D
{
    typedef long(__fastcall* DXGIPresentFunc)(IDXGISwapChain3* SwapChainPtr, uint SyncInterval, uint Flags);
    typedef HRESULT(__fastcall* DXGIResizeBuffersFunc)(IDXGISwapChain* SwapChainPtr, uint BufferCount, uint Width,
        uint Height, DXGI_FORMAT NewFormat, uint SwapChainFlags);
    typedef ulong(__fastcall* DXGIReleaseFunc)(IDXGISwapChain3* SwapChainPtr);

    global DXGIPresentFunc DXGIPresentOriginal = {};
    global DXGIResizeBuffersFunc DXGIResizeBuffersOriginal = {};
    global DXGIReleaseFunc DXGIReleaseOriginal = {};

    [[maybe_unused]] fun IsDXGIPresentHooked()->bool;
    [[maybe_unused]] fun IsDXGIResizeBuffersHooked()->bool;
    [[maybe_unused]] fun IsDXGIReleaseHooked()->bool;

    fun HookDXGIPresent(DXGIPresentFunc f)->void;
    fun UnhookDXGIPresent()->void;

    fun HookDXGIResizeBuffers(DXGIResizeBuffersFunc f)->void;
    fun UnhookDXGIResizeBuffers()->void;

    fun HookDXGIRelease(DXGIReleaseFunc f)->void;
    fun UnhookDXGIRelease()->void;
}

#include <indxe>
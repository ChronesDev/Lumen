#pragma once

#include <lumen/ext/dx/dx.cc>

#include <indx>

#include <indxs>

namespace Lumen::Render::D2D
{
    typedef long(__fastcall* DXGIPresentFunc)(IDXGISwapChain3* SwapChainPtr, uint SyncInterval, uint Flags);
    typedef long(__fastcall* DXGIPresent1Func)(
        IDXGISwapChain3* SwapChainPtr, uint SyncInterval, const DXGI_PRESENT_PARAMETERS* PresentParameters);
    typedef HRESULT(__fastcall* DXGIResizeBuffersFunc)(IDXGISwapChain* SwapChainPtr, uint BufferCount, uint Width,
        uint Height, DXGI_FORMAT NewFormat, uint SwapChainFlags);
    typedef ulong(__fastcall* DXGIReleaseFunc)(IDXGISwapChain3* SwapChainPtr);

    global DXGIPresentFunc DXGIPresentOriginal = {};
    global DXGIPresent1Func DXGIPresent1Original = {};
    global DXGIResizeBuffersFunc DXGIResizeBuffersOriginal = {};
    global DXGIReleaseFunc DXGIReleaseOriginal = {};

    [[maybe_unused]] fun IsDXGIPresentHooked()->bool;
    [[maybe_unused]] fun IsDXGIPresent1Hooked()->bool;
    [[maybe_unused]] fun IsDXGIResizeBuffersHooked()->bool;
    [[maybe_unused]] fun IsDXGIReleaseHooked()->bool;

    fun HookDXGIPresent(DXGIPresentFunc f)->void;
    fun UnhookDXGIPresent()->void;

    fun HookDXGIPresent1(DXGIPresent1Func f)->void;
    fun UnhookDXGIPresent1()->void;

    fun HookDXGIResizeBuffers(DXGIResizeBuffersFunc f)->void;
    fun UnhookDXGIResizeBuffers()->void;

    fun HookDXGIRelease(DXGIReleaseFunc f)->void;
    fun UnhookDXGIRelease()->void;
}

#include <indxe>
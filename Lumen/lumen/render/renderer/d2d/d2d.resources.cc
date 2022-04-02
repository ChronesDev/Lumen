#pragma once

#include <winrt/base.h>

#include <lumen/ext/dx/dx.cc>
#include <lumen/ext/d2d/d2d.cc>

#include <indx>

#include "d2d.framecontext.cc"

#include <indxs>

namespace Lumen::Render::D2D::Res
{
    using winrt::com_ptr;

    fun ReleaseAll()->void;

    global IDXGISwapChain3* SwapChain = nullptr;
    global ID3D12CommandQueue* D3D12CommandQueue = nullptr;

    global com_ptr<ID3D12Device> D3D12Device = nullptr;
    global com_ptr<ID3D12DescriptorHeap> D3D12DescriptorHeap = nullptr;
    global com_ptr<IDXGIDevice> DXGIDevice = nullptr;
    global List<com_ptr<IDXGISurface1>> DXGISurfaces;
    global List<FrameContext> FrameContext;

    global com_ptr<ID3D11Device> D3D11Device = nullptr;
    global com_ptr<ID3D11DeviceContext> D3D11DeviceContext = nullptr;
    global com_ptr<ID3D11On12Device> D3D11On12Device = nullptr;
    global List<com_ptr<ID3D11Resource>> D3D11Resources;

    global com_ptr<ID2D1Factory7> D2D1Factory = nullptr;
    global com_ptr<ID2D1Device6> D2D1Device = nullptr;
    global com_ptr<ID2D1DeviceContext6> D2D1DeviceContext = nullptr;
    global List<com_ptr<ID2D1RenderTarget>> D2D1RenderTargets;
    global List<com_ptr<ID2D1Bitmap1>> D2D1Bitmaps;

    global uint BufferCount = 0;
    global float Dpi = 96.0f;
}

#include <indxe>
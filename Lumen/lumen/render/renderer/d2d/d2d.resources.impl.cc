#include "d2d.resources.cc"

#include <indxs>

namespace Lumen::Render::D2D::Res
{
    fun ReleaseAll()->void
    {
        SwapChain = {};
        D3D12CommandQueue = {};

        D3D12Device = {};
        D3D12DescriptorHeap = {};
        DXGIDevice = {};
        DXGISurfaces = {};

        D3D11Device = {};
        D3D11DeviceContext = {};
        D3D11On12Device = {};
        D3D11Resources = {};

        D2D1Factory = {};
        D2D1Device = {};
        D2D1DeviceContext = {};
        D2D1RenderTargets = {};
        D2D1Bitmaps = {};

        BufferCount = 0;

        FrameContext = {};
    }
}

#include <indxe>
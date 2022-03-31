#include <lumen/ext/kiero/kiero.cc>

#include "d2d.cc"

#include <indxs>

namespace Lumen::Render::D2D
{
    using winrt::com_ptr;

    static fun RenderInit_()->void;
    static fun RenderDeinit_()->void;
    static fun RenderRelease_()->void;
    static fun RenderReleaseSub_()->void;

    static fun OnPresent_(IDXGISwapChain3* SwapChainPtr, uint SyncInterval, uint Flags)->HRESULT;
    static fun OnResizeBuffers_(IDXGISwapChain* SwapChainPtr, uint BufferCount, uint Width, uint Height,
        DXGI_FORMAT NewFormat, uint SwapChainFlags)
        ->HRESULT;
    static fun OnExecuteCommandLists_(
        ID3D12CommandQueue* CommandQueuePtr, uint CommandListsCount, ID3D12CommandList* CommandListPtr)
        ->void;

    static fun OnRenderInit_()->void;
    static fun OnRender_()->void;

    static bool Initialized_ = false;
    fun HasInit()->bool { return Initialized_; }

    fun Init()->void
    {
        if (Initialized_) INDEX_THROW("Already initialized.");

        Ext::Kiero::Init(kiero::RenderType::D3D12);

        RenderInit_();

        Initialized_ = true;
    }
    fun Deinit()->void
    {
        if (!Initialized_) INDEX_THROW("Already deinitialized.");

        RenderDeinit_();

        Ext::Kiero::Deinit();

        Initialized_ = false;
    }

    static bool InitializeOnNextCall_ = false;
    static bool ReleaseOnNextCall_ = false;
    static bool IgnoreRender_ = false;

    namespace res = Res;
    static IDXGISwapChain3* SwapChain_ = nullptr;
    static ID3D12CommandQueue* D3D12CommandQueue_ = nullptr;

    static int SkipFrames = 0;

    static uint Width = 0;
    static uint Height = 0;

    static uint CurrentBufferIndex = 0;

    static fun RenderInit_()->void
    {
        HookDXGIPresent(OnPresent_);
        HookDXGIResizeBuffers(OnResizeBuffers_);
        HookD3D12ExecuteCommandLists(OnExecuteCommandLists_);

        InitializeOnNextCall_ = true;
        IgnoreRender_ = false;
    }
    static fun RenderDeinit_()->void
    {
        if (IsDXGIPresentHooked()) UnhookDXGIPresent();
        if (IsDXGIResizeBuffersHooked()) UnhookDXGIResizeBuffers();
        if (IsD3D12ExecuteCommandListsHooked()) UnhookD3D12ExecuteCommandLists();

        RenderRelease_();

        InitializeOnNextCall_ = false;
        IgnoreRender_ = true;
    }

    static fun RenderRelease_()->void
    {
        DXRelease.Invoke();
        res::ReleaseAll();
        RenderReleaseSub_();
        InitializeOnNextCall_ = true;
    }
    static fun RenderReleaseSub_()->void
    {
        SwapChain_ = {};
        D3D12CommandQueue_ = {};

        CurrentBufferIndex = 0;
    }

    static fun OnPresent_(IDXGISwapChain3* SwapChainPtr, uint SyncInterval, uint Flags)->HRESULT
    {
        // Present

        SwapChain_ = SwapChainPtr;
        res::SwapChain = SwapChain_;

        // Skip Frames if needed
        {
            if (SkipFrames < 0) { SkipFrames = 0; }
            elif (SkipFrames > 0)
            {
                SkipFrames--;
                goto jmp_return;
            }
        }

        if (IgnoreRender_) goto jmp_return;

        OnRenderInit_();
        OnRender_();

    jmp_return:
        var result = DXGIPresentOriginal(SwapChainPtr, SyncInterval, Flags);

        DXRenderCompleted.Invoke();

        return result;
    }

    static fun OnResizeBuffers_(IDXGISwapChain* SwapChainPtr, uint BufferCount, uint Width, uint Height,
        DXGI_FORMAT NewFormat, uint SwapChainFlags)
        ->HRESULT
    {
        SkipFrames = 10;

        RenderRelease_();

        return DXGIResizeBuffersOriginal(SwapChainPtr, BufferCount, Width, Height, NewFormat, SwapChainFlags);
    }

    static fun OnExecuteCommandLists_(
        ID3D12CommandQueue* CommandQueuePtr, uint CommandListsCount, ID3D12CommandList* CommandListPtr)
        ->void
    {
        if (D3D12CommandQueue_ == nullptr)
        {
            D3D12CommandQueue_ = CommandQueuePtr;
            res::D3D12CommandQueue = D3D12CommandQueue_;
        }

        return D3D12ExecuteCommandListsOriginal(CommandQueuePtr, CommandListsCount, CommandListPtr);
    }

    static fun OnRenderInit_()->void
    {
        // Initialize

        if (res::D3D12CommandQueue == nullptr) return;

        if (!InitializeOnNextCall_) return;
        InitializeOnNextCall_ = false;

        if (SwapChain_->GetDevice(__uuidof(ID3D12Device), res::D3D12Device.put_void()) != S_OK)
        {
            INDEX_THROW("Your device does not support DirectX12 for Minecraft.");
        }

        // Create D311On12Device
        com_ptr<ID3D12CommandQueue> commandQueue;
        commandQueue.attach(res::D3D12CommandQueue);
        ThrowIfFailed(D3D11On12CreateDevice((IUnknown*)res::D3D12Device.get(),
            D3D11_CREATE_DEVICE_FLAG::D3D11_CREATE_DEVICE_SINGLETHREADED
                | D3D11_CREATE_DEVICE_FLAG::D3D11_CREATE_DEVICE_BGRA_SUPPORT,
            nullptr, 0, (IUnknown**)&res::D3D12CommandQueue, 1, 0, res::D3D11Device.put(),
            res::D3D11DeviceContext.put(), nullptr));

        res::D3D11On12Device = res::D3D11Device.as<ID3D11On12Device>();
        res::DXGIDevice = res::D3D11On12Device.as<IDXGIDevice>();

        // Create D2D1Factory and D2D1Device
        {
            D2D1_DEVICE_CONTEXT_OPTIONS device_options = D2D1_DEVICE_CONTEXT_OPTIONS_NONE;
            D2D1_FACTORY_OPTIONS factory_options {};
            ThrowIfFailed(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory3),
                &factory_options, res::D2D1Factory.put_void()));

            ThrowIfFailed(res::D2D1Factory->CreateDevice(res::DXGIDevice.get(), res::D2D1Device.put()));
            ThrowIfFailed(res::D2D1Device->CreateDeviceContext(device_options, res::D2D1DeviceContext.put()));
        }

        // GetBufferCount
        {
            DXGI_SWAP_CHAIN_DESC swapChainDescription;
            SwapChain_->GetDesc(&swapChainDescription);
            res::BufferCount = swapChainDescription.BufferCount;
        }

        // GetRTVHandles and Setup FrameContexts
        {
            var bufferCount = res::BufferCount;
            res::FrameContext = MakeSizedList<FrameContext>(bufferCount);
            res::D3D11Resources = MakeSizedList<com_ptr<ID3D11Resource>>(bufferCount);
            res::DXGISurfaces = MakeSizedList<com_ptr<IDXGISurface1>>(bufferCount);
            res::D2D1RenderTargets = MakeSizedList<com_ptr<ID2D1RenderTarget>>(bufferCount);
            res::D2D1Bitmaps = MakeSizedList<com_ptr<ID2D1Bitmap1>>(bufferCount);

            D3D12_DESCRIPTOR_HEAP_DESC heapDescriptorBackBuffers = {};
            heapDescriptorBackBuffers.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
            heapDescriptorBackBuffers.NumDescriptors = res::BufferCount;
            heapDescriptorBackBuffers.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
            heapDescriptorBackBuffers.NodeMask = 1;

            ThrowIfFailed(res::D3D12Device->CreateDescriptorHeap(
                &heapDescriptorBackBuffers, IID_PPV_ARGS(res::D3D12DescriptorHeap.put())));

            uint rtvDescriptorSize
                = res::D3D12Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
            D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = res::D3D12DescriptorHeap->GetCPUDescriptorHandleForHeapStart();

            var dpi = (float)GetDpiForSystem();
            res::Dpi = dpi;

            for (int i = 0; i < bufferCount; i++)
            {
                ID3D12Resource* backBufferPtr = nullptr;
                res::FrameContext[i].MainRenderTargetDescriptor = rtvHandle;
                ThrowIfFailed(SwapChain_->GetBuffer(i, IID_PPV_ARGS(&backBufferPtr)));
                res::D3D12Device->CreateRenderTargetView(backBufferPtr, nullptr, rtvHandle);
                res::FrameContext[i].MainRenderTargetResourcePtr = backBufferPtr;
                rtvHandle.ptr += rtvDescriptorSize;
                D3D12_RESOURCE_DESC backBufferDescriptor = backBufferPtr->GetDesc();
                Width = backBufferDescriptor.Width;
                Height = backBufferDescriptor.Height;

                D3D11_RESOURCE_FLAGS d3d11_flags = { D3D11_BIND_RENDER_TARGET };
                ThrowIfFailed(res::D3D11On12Device->CreateWrappedResource(backBufferPtr, &d3d11_flags,
                    D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT,
                    IID_PPV_ARGS(res::D3D11Resources[i].put())));

                ThrowIfFailed(res::D3D11Resources[i]->QueryInterface(res::DXGISurfaces[i].put()));

                // Surface
                {
                    /*D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(
                            D2D1_RENDER_TARGET_TYPE_DEFAULT,
                            D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED),
                            dpi,
                            dpi
                    );

                    res::D2D1Factory->CreateDxgiSurfaceRenderTarget(
                            res::DXGISurfaces[i].get(),
                            &props,
                            res::D2D1RenderTargets[i].put()
                    );*/
                }

                // BitMap
                {
                    D2D1_BITMAP_PROPERTIES1 props
                        = D2D1::BitmapProperties1(D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
                            D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED), dpi, dpi);
                    res::D2D1DeviceContext->CreateBitmapFromDxgiSurface(
                        res::DXGISurfaces[i].get(), props, res::D2D1Bitmaps[i].put());
                }
            }
        }

        // DXRenderInit
        DXRenderInit.Invoke();
    }

    static fun OnRender_()->void
    {
        // Render Frame

        if (res::D2D1Bitmaps.Length == 0) return;

        CurrentBufferIndex = SwapChain_->GetCurrentBackBufferIndex();
        var* dc = res::D2D1DeviceContext.get();
        var i = CurrentBufferIndex;

        // Begin Render
        const var d3d11Resources = res::D3D11Resources[i].get();
        res::D3D11On12Device->AcquireWrappedResources(&d3d11Resources, 1);
        dc->SetTarget(res::D2D1Bitmaps[i].get());
        dc->BeginDraw();

        // DXRender
        DXRender.Invoke();

        ThrowIfFailed(dc->EndDraw());
        dc->BeginDraw();

        {
            var r = D2D1::RoundedRect(
                D2D1::RectF(10, 10, 40, 40),
                5, 5);
            var c = D2D1::ColorF(D2D1::ColorF::Red);
            com_ptr<ID2D1SolidColorBrush> b;
            dc->CreateSolidColorBrush(c, b.put());
            dc->FillRoundedRectangle(r, b.get());

            ThrowIfFailed(dc->EndDraw());
            dc->BeginDraw();
        }

        // End Render
        ThrowIfFailed(dc->EndDraw());

        res::D3D11On12Device->ReleaseWrappedResources(&d3d11Resources, 1);
        res::D3D11DeviceContext->Flush();
    }
}

#include <indxe>
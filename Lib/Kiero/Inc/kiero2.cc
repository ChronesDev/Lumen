#include "kiero2"

#include <exception>

#if KIERO_INCLUDE_D3D12
#include <d3d12.h>
#include <dxgi1_2.h>
#endif

#ifdef _UNICODE
#define KIERO_TEXT(text) L##text
#else
#define KIERO_TEXT(text) text
#endif

static void* VTableMember(void* cls, unsigned int offset)
{
    uintptr_t* vtable = *(uintptr_t**)cls;
    return (void*)(vtable[offset]);
}

namespace kiero
{
    static bool IDXGISwapchain1_Bindings_Initialized_ = false;

    void unbind_MH_RemoveHook(uint16_t _index)
    {
        auto g_renderType = getRenderType();
        auto g_methodsTable = getMethodsTable();

        if (g_renderType != RenderType::None)
        {
            unbind(_index);
            MH_RemoveHook((void*)g_methodsTable[_index]);
        }
    }

#if KIERO_INCLUDE_D3D12
    bool has_init_IDXGISwapchain1_Bindings_() { return IDXGISwapchain1_Bindings_Initialized_; }

    kiero::Status::Enum init_IDXGISwapchain1_Bindings_()
    {
        if (IDXGISwapchain1_Bindings_Initialized_) return Status::AlreadyInitializedError;

        IDXGISwapchain1_Bindings_ = {};
        for (int i = 0; i < IDXGISwapchain1_Bindings_Length_; i++)
        {
            IDXGISwapchain1_Bindings_.push_back(nullptr);
        }

        WNDCLASSEX windowClass;
        windowClass.cbSize = sizeof(WNDCLASSEX);
        windowClass.style = CS_HREDRAW | CS_VREDRAW;
        windowClass.lpfnWndProc = DefWindowProc;
        windowClass.cbClsExtra = 0;
        windowClass.cbWndExtra = 0;
        windowClass.hInstance = GetModuleHandle(NULL);
        windowClass.hIcon = NULL;
        windowClass.hCursor = NULL;
        windowClass.hbrBackground = NULL;
        windowClass.lpszMenuName = NULL;
        windowClass.lpszClassName = KIERO_TEXT("Kiero");
        windowClass.hIconSm = NULL;

        ::RegisterClassEx(&windowClass);

        HWND window = ::CreateWindow(windowClass.lpszClassName, KIERO_TEXT("Kiero DirectX Window"),
            WS_OVERLAPPEDWINDOW, 0, 0, 100, 100, NULL, NULL, windowClass.hInstance, NULL);

        HMODULE libDXGI;
        HMODULE libD3D12;
        if ((libDXGI = ::GetModuleHandle(KIERO_TEXT("dxgi.dll"))) == NULL
            || (libD3D12 = ::GetModuleHandle(KIERO_TEXT("d3d12.dll"))) == NULL)
        {
            ::DestroyWindow(window);
            ::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
            return Status::ModuleNotFoundError;
        }

        void* CreateDXGIFactory2;
        if ((CreateDXGIFactory2 = ::GetProcAddress(libDXGI, "CreateDXGIFactory2")) == NULL)
        {
            ::DestroyWindow(window);
            ::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
            return Status::UnknownError;
        }

        IDXGIFactory2* factory;
        if (((long(__stdcall*)(UINT, const IID&, void**))(CreateDXGIFactory2))(0, __uuidof(IDXGIFactory2), (void**)&factory) < 0)
        {
            ::DestroyWindow(window);
            ::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
            return Status::UnknownError;
        }

        IDXGIAdapter1* adapter;
        if (factory->EnumAdapters1(0, &adapter) == DXGI_ERROR_NOT_FOUND)
        {
            ::DestroyWindow(window);
            ::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
            return Status::UnknownError;
        }

        void* D3D12CreateDevice;
        if ((D3D12CreateDevice = ::GetProcAddress(libD3D12, "D3D12CreateDevice")) == NULL)
        {
            ::DestroyWindow(window);
            ::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
            return Status::UnknownError;
        }

        ID3D12Device* device;
        if (((long(__stdcall*)(IUnknown*, D3D_FEATURE_LEVEL, const IID&, void**))(D3D12CreateDevice))(
                adapter, D3D_FEATURE_LEVEL_11_0, __uuidof(ID3D12Device), (void**)&device)
            < 0)
        {
            ::DestroyWindow(window);
            ::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
            return Status::UnknownError;
        }

        D3D12_COMMAND_QUEUE_DESC queueDesc;
        queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
        queueDesc.Priority = 0;
        queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
        queueDesc.NodeMask = 0;

        ID3D12CommandQueue* commandQueue;
        if (device->CreateCommandQueue(&queueDesc, __uuidof(ID3D12CommandQueue), (void**)&commandQueue) < 0)
        {
            ::DestroyWindow(window);
            ::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
            return Status::UnknownError;
        }

        ID3D12CommandAllocator* commandAllocator;
        if (device->CreateCommandAllocator(
                D3D12_COMMAND_LIST_TYPE_DIRECT, __uuidof(ID3D12CommandAllocator), (void**)&commandAllocator)
            < 0)
        {
            ::DestroyWindow(window);
            ::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
            return Status::UnknownError;
        }

        ID3D12GraphicsCommandList* commandList;
        if (device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, commandAllocator, NULL,
                __uuidof(ID3D12GraphicsCommandList), (void**)&commandList)
            < 0)
        {
            ::DestroyWindow(window);
            ::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
            return Status::UnknownError;
        }

        DXGI_RATIONAL refreshRate;
        refreshRate.Numerator = 60;
        refreshRate.Denominator = 1;

        DXGI_MODE_DESC bufferDesc;
        bufferDesc.Width = 100;
        bufferDesc.Height = 100;
        bufferDesc.RefreshRate = refreshRate;
        bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
        bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

        DXGI_SAMPLE_DESC sampleDesc;
        sampleDesc.Count = 1;
        sampleDesc.Quality = 0;

        DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
        swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        swapChainDesc.Stereo = TRUE;
        swapChainDesc.SampleDesc = sampleDesc;
        swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapChainDesc.BufferCount = 2;
        swapChainDesc.Scaling = DXGI_SCALING_STRETCH;
        swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
        swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_IGNORE;
        swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

        IDXGISwapChain1* swapChain;
        if (factory->CreateSwapChainForHwnd(commandQueue, window, &swapChainDesc, nullptr, nullptr, &swapChain) < 0)
        {
            ::DestroyWindow(window);
            ::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
            return Status::UnknownError;
        }

        ::memcpy(IDXGISwapchain1_Bindings_.data(), *(uint150_t**)swapChain, IDXGISwapchain1_Bindings_.size() * sizeof(uint150_t));
        IDXGISwapchain1_Bindings_Initialized_ = true;

#if KIERO_USE_MINHOOK
        MH_Initialize();
#endif

        device->Release();
        device = NULL;

        commandQueue->Release();
        commandQueue = NULL;

        commandAllocator->Release();
        commandAllocator = NULL;

        commandList->Release();
        commandList = NULL;

        swapChain->Release();
        swapChain = NULL;

        ::DestroyWindow(window);
        ::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);

        IDXGISwapchain1_Bindings_Initialized_ = true;
        return Status::Success;
    }

    void shutdown_IDXGISwapchain1_Bindings_()
    {
        IDXGISwapchain1_Bindings_ = {};
        IDXGISwapchain1_Bindings_Initialized_ = false;
    }

    kiero::Status::Enum bind_IDXGISwapchain1_Bindings_(uint16_t _index, void** _original, void* _function)
    {
        if (!_original || !_function) return Status::UnknownError;

        if (kiero::getRenderType() != RenderType::None)
        {
#if KIERO_USE_MINHOOK
            void* target = (void*)IDXGISwapchain1_Bindings_[_index];
            if (!target) return Status::UnknownError;

            if (MH_CreateHook(target, _function, _original) != MH_OK || MH_EnableHook(target) != MH_OK)
            {
                return Status::UnknownError;
            }
#endif
        }

        return Status::Success;
    }

    void unbind_IDXGISwapChain1_Bindings_(uint16_t _index)
    {
        if (kiero::getRenderType() != RenderType::None)
        {
#if KIERO_USE_MINHOOK
            if (!IDXGISwapchain1_Bindings_[_index]) return;
            MH_DisableHook((void*)IDXGISwapchain1_Bindings_[_index]);
#endif
        }
    }

    void unbind_IDXGISwapchain1_Bindings_MH_RemoveHook_(uint16_t _index)
    {
        auto g_renderType = getRenderType();
        auto g_methodsTable = getMethodsTable();

        if (kiero::getRenderType() != RenderType::None)
        {
            unbind(_index);
            MH_RemoveHook((void*)IDXGISwapchain1_Bindings_[_index]);
        }
    }
#endif
}
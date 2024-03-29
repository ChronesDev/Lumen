#include <lumen/render/render.cc>
#include <lumen/ui/lui/lui.cc>

#include "lu.cc"

#include <indxs-ui>
#include <indxs>

namespace Lumen::UI
{
    IPtr<LUIContext> LContext;
    UIFrameCounter FrameCounter;

    fun Init()->void
    {
        //return;
        LContext = INew<LUIContext>();

        Render::D2D::DXRender += OnRender;
        Render::D2D::DXRenderInit += OnInitRender;
        Render::D2D::DXRelease += OnRelease;

        LContext->AttachRootElement(GetUI());

        InitInput();
    }
    fun Deinit()->void
    {
        //return;
        Render::D2D::DXRender -= OnRender;
        Render::D2D::DXRenderInit -= OnInitRender;
        Render::D2D::DXRelease -= OnRelease;

        DeinitInput();
    }

    fun OnRender()->void
    {
        var now = Time.Now;

        LContext->SetDrawContext(Render::D2D::Res::D2D1DeviceContext);

        LContext->Compute(FrameCounter.Next(), { 0.f, 0.f, (float)Render::D2D::Width, (float)Render::D2D::Height });
        if (auto e = LContext->RootElement)
        {
            e->ForceComputeLayout();
        }
        LContext->Render();
        LContext->Update();

        var lasted = (Time.Now - now).Micro;
        // Console.Log("Time Lasted: ", lasted);
    }
    
    fun OnInitRender()->void
    {
        LContext->RootElement->ForceComputeLayout();
    }

    fun OnRelease()->void { LContext->SetDrawContext(nullptr); }
}

#include <indxe-ui>
#include <indxe>
#include <lumen/render/render.cc>
#include <lumen/ui/lui/lui.cc>

#include "lu.cc"

#include <indxs-ui>
#include <indxs>

namespace Lumen::UI
{
    static IPtr<LUIContext> LContext;
    static UIFrameCounter FrameCounter;

    fun Init()->void
    {
        LContext = INew<LUIContext>();

        Render::D2D::DXRender += OnRender;
        Render::D2D::DXRenderInit += OnInitRender;
        Render::D2D::DXRelease += OnRelease;

        LContext->AttachRootElement(GetUI());
    }
    fun Deinit()->void
    {
        Render::D2D::DXRender -= OnRender;
        Render::D2D::DXRenderInit -= OnInitRender;
        Render::D2D::DXRelease -= OnRelease;
    }

    fun OnRender()->void
    {
        LContext->SetDrawContext(Render::D2D::Res::D2D1DeviceContext);

        FrameCounter.Next();
        LContext->Compute(FrameCounter.Frame, { 0.f, 0.f, (float)Render::D2D::Width, (float)Render::D2D::Height });
        LContext->Render();
        LContext->Update();
    }

    fun OnInitRender()->void { }

    fun OnRelease()->void { LContext->SetDrawContext({}); }
}

#include <indxe-ui>
#include <indxe>
#pragma once

#include <lumen/ui/lui/common/common.cc>

#include <lumen/ui/lui/element/element.cc>
#include <lumen/ui/lui/resource/resource.cc>

#include <indxs>

namespace Lumen::LUI
{
    INDEX_UI_Declare(OutRect);

    struct OutRect : virtual LUIRenderElement
    {
        INDEX_UI_UseMapper(OutRectMapper);

    public:
        ColorBrushResource Outline;
        float Thickness = 1.f;

    protected:
        void OnLRender(LUIDrawable* d) override
        {
            if (!Outline.HasResource) return;
            d->DrawRectangle(ToD2DRectF(ComputedLayout), Outline.Resource.get(), Thickness);
        }

    protected:
        fun OnResourcesUpdate()->void override { Outline.Update(lc); }
        fun OnResourcesRelease()->void override { Outline.Release(); }
    };

    struct OutRectMapper : virtual UIElementMapper
    {
    public:
        Color Outline;

    public:
        IPtr<UIElement> Make() override
        {
            IPtr<OutRect> e_ref = INew<OutRect>();
            OutRect& e = e_ref.Value;

            Impl_(e);
            Impl_OutRect_(e);

            return e_ref.DynamicAs<UIElement>();
        }

        template <class T> void Impl_OutRect_(T& e) { e.Outline.Value = Outline; }
    };
}

#include <indxe>
#pragma once

#include <lumen/ui/lui/common/common.cc>

#include <lumen/ui/lui/element/element.cc>
#include <lumen/ui/lui/resource/resource.cc>

#include <indxs>

namespace Lumen::LUI
{
    INDEX_UI_Declare(FillRect);

    struct FillRect : virtual LUIRenderElement
    {
        INDEX_UI_UseMapper(FillRectMapper);

    public:
        ColorBrushResource Fill;

    protected:
        void OnLRender(LUIDrawable* d) override
        {
            if (!Fill.HasResource) return;
            d->FillRectangle(ToD2DRectF(ComputedLayout), Fill.Resource.get());
        }

    protected:
        fun OnResourcesUpdate()->void override { Fill.Update(lc); }
        fun OnResourcesRelease()->void override { Fill.Release(); }
    };

    struct FillRectMapper : virtual UIElementMapper
    {
    public:
        Color Fill;

    public:
        IPtr<UIElement> Make() override
        {
            IPtr<FillRect> e_ref = INew<FillRect>();
            FillRect& e = e_ref.Value;

            Impl_(e);
            Impl_FillRect_(e);

            return e_ref.DynamicAs<UIElement>();
        }

        template <class T> void Impl_FillRect_(T& e) { e.Fill.Value = Fill; }
    };
}

#include <indxe>
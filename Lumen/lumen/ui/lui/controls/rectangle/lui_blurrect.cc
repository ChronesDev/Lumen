#pragma once

#include <lumen/ui/lui/common/common.cc>

#include <lumen/ui/lui/element/element.cc>
#include <lumen/ui/lui/resource/resource.cc>

#include <indxs>

namespace Lumen::LUI
{
    INDEX_UI_Declare(BlurRect);

    struct BlurRect : virtual LUIRenderElement
    {
        INDEX_UI_UseMapper(BlurRectMapper);

    protected:
        void OnLRender(LUIDrawable* d) override
        {
            d->PushAxisAlignedClip(ToD2DRectF(ComputedLayout), {});
            d->DrawImage(lc->BlurBuffer);
            d->PopAxisAlignedClip();
        }

    protected:
        fun OnResourcesUpdate()->void override { }
        fun OnResourcesRelease()->void override { }
    };

    struct BlurRectMapper : virtual UIElementMapper
    {
    public:
        IPtr<UIElement> Make() override
        {
            IPtr<BlurRect> e_ref = INew<BlurRect>();
            BlurRect& e = e_ref.Value;

            Impl_(e);

            return e_ref.DynamicAs<UIElement>();
        }
    };
}

#include <indxe>
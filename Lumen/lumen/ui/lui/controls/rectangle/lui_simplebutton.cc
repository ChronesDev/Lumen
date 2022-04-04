#pragma once

#include <lumen/ui/lui/common/common.cc>

#include <lumen/ui/lui/element/element.cc>
#include <lumen/ui/lui/resource/resource.cc>

#include <indxs>

namespace Lumen::LUI
{
    INDEX_UI_Declare(SimpleButton);

    struct SimpleButton : virtual LUIRenderElement, virtual LUIButton
    {
        INDEX_UI_UseMapper(SimpleButtonMapper);

    public:
        ColorBrushResource Fill { Colors::Blue };
        ColorBrushResource FillSelected { Colors::Aqua };
        ColorBrushResource FillPressed { Colors::White };

        Event<void(SimpleButton* e)> Clicked;

    protected:
        void OnLRender(LUIDrawable* d) override
        {
            if (!Fill.HasResource) return;
            if (!FillSelected.HasResource) return;
            if (!FillPressed.HasResource) return;

            if (IsPressed) [[unlikely]]
            {
                d->FillRectangle(ToD2DRectF(ComputedLayout), FillPressed.Resource.get());
                return;
            }

            elif (IsSelected)
            {
                d->FillRectangle(ToD2DRectF(ComputedLayout), FillSelected.Resource.get());
                return;
            }

            else [[likely]]
            {
                d->FillRectangle(ToD2DRectF(ComputedLayout), Fill.Resource.get());
                return;
            }
        }

    protected:
        fun OnResourcesUpdate()->void override
        {
            Fill.Update(lc);
            FillSelected.Update(lc);
            FillPressed.Update(lc);
        }
        fun OnResourcesRelease()->void override
        {
            Fill.Release();
            FillSelected.Release();
            FillPressed.Release();
        }

    protected:
        fun SimpleButton_OnClicked()->void {
            Clicked.Invoke(this);
        }
        fun OnClicked()->void override
        {
            SimpleButton_OnClicked();
            LUIButton::OnClicked();
        }
    };

    struct SimpleButtonMapper : virtual UIElementMapper
    {
    public:
        Event<void(SimpleButton* e)> Clicked;

    public:
        IPtr<UIElement> Make() override
        {
            IPtr<SimpleButton> e_ref = INew<SimpleButton>();
            SimpleButton& e = e_ref.Value;

            Impl_(e);
            Impl_SimpleButton_(e);

            return e_ref.DynamicAs<SimpleButton>();
        }

        template <class T> void Impl_SimpleButton_(T& e) { e.Clicked = Clicked; }
    };
}

#include <indxe>
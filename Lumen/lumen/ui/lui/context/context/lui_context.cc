#pragma once

#include <lumen/render/renderer/d2d/d2d.cc>
#include <lumen/ui/lui/common/common.cc>

#include "lui_descriptor.cc"

#include <indxs>

namespace Lumen::LUI
{
    struct LUIContext : virtual UIInputContext<LUIInputDescriptor>
    {
    protected:
        winrt::com_ptr<LUIDrawable> DrawContext_;

    public:
        fun SetDrawContext(const winrt::com_ptr<LUIDrawable>& value)
        {
            if (DrawContext_ != value)
            {
                DrawContext_ = value;
                if (value) ResourcesUpdate();
                else
                    ResourcesRelease();
            }
        }

    public:
        fun GetDrawContext() const->LUIDrawable* { return DrawContext_.get(); }
        INDEX_Property(get = GetDrawContext) LUIDrawable* dw;

    protected:
        fun TriggerResourcesUpdate()->void
        {
            for (var& v : ResourcesUpdateSubscribers)
            {
                if (!v.first) continue;
                if (!v.second) continue;
                v.second();
            }
        }
        fun TriggerResourcesRelease()->void
        {
            for (var& v : ResourcesReleaseSubscribers)
            {
                if (!v.first) continue;
                if (!v.second) continue;
                v.second();
            }
        }

    public:
        std::list<std::pair<IPtr<UIElement>, std::function<void()>>> ResourcesUpdateSubscribers;

        fun AddResourcesUpdateCallback(const IPtr<UIElement>& e, const std::function<void()>& f)->void
        {
            ResourcesUpdateSubscribers.emplace_back(e, f);
        }
        fun RemoveResourcesUpdateCallback(const IPtr<UIElement>& e)->void
        {
            var p = e.Ptr;
            ResourcesUpdateSubscribers.remove_if([p](const auto& it) { return it.first.Ptr == p; });
        }

    public:
        std::list<std::pair<IPtr<UIElement>, std::function<void()>>> ResourcesReleaseSubscribers;

        fun AddResourcesReleaseCallback(const IPtr<UIElement>& e, const std::function<void()>& f)->void
        {
            ResourcesReleaseSubscribers.emplace_back(e, f);
        }
        fun RemoveResourcesReleaseCallback(const IPtr<UIElement>& e)->void
        {
            var p = e.Ptr;
            ResourcesReleaseSubscribers.remove_if([p](const auto& it) { return it.first.Ptr == p; });
        }

    protected:
        winrt::com_ptr<ID2D1Bitmap1> BackBuffer_;
        winrt::com_ptr<ID2D1Image> BlurBuffer_;
        winrt::com_ptr<ID2D1Effect> BlurEffect_;

    public:
        fun GetBackBuffer() const->ID2D1Bitmap1*
        {
            if (!BackBuffer_) INDEX_THROW("BackBuffer was null.");
            return BackBuffer_.get();
        }
        INDEX_Property(get = GetBackBuffer) ID2D1Bitmap1* BackBuffer;

        fun GetBlurBuffer() const->ID2D1Image*
        {
            if (!BlurBuffer_) INDEX_THROW("BlurBuffer was null.");
            return BlurBuffer_.get();
        }
        INDEX_Property(get = GetBlurBuffer) ID2D1Image* BlurBuffer;

    public:
        void Render() override
        {
            if (dw == nullptr) return;

            namespace d2d = ::Lumen::Render::D2D;

            if (DrawContext_ == nullptr) INDEX_THROW("DrawContext_ (dw) was nullptr.");

            d2d::CopyBitmap(
                DrawContext_.get(), d2d::Res::D2D1Bitmaps[d2d::CurrentBufferIndex], BackBuffer_);

            if (BlurEffect_ == nullptr)
            {
                d2d::ThrowIfFailed(DrawContext_->CreateEffect(CLSID_D2D1GaussianBlur, BlurEffect_.put()));
                BlurEffect_->SetValue(D2D1_GAUSSIANBLUR_PROP_STANDARD_DEVIATION, 10.0f);
                BlurEffect_->SetValue(D2D1_GAUSSIANBLUR_PROP_OPTIMIZATION, D2D1_GAUSSIANBLUR_OPTIMIZATION_SPEED);
                BlurEffect_->SetValue(D2D1_GAUSSIANBLUR_PROP_BORDER_MODE, D2D1_BORDER_MODE_HARD);
            }
            BlurEffect_->SetInput(0, BackBuffer_.get());

            d2d::MakeBlurBufferArgs args {
                .BackBuffer = BackBuffer_, .BlurBuffer = BlurBuffer_, .BlurEffect = &BlurEffect_, .Sigma = 10.0f
            };
            d2d::MakeBlurBuffer(DrawContext_.get(), args);

            UIRoot::Render();
        }

    public:
        fun ResourcesUpdate()->void { TriggerResourcesUpdate(); }

        fun ResourcesRelease()->void
        {
            DrawContext_ = nullptr;

            BackBuffer_ = nullptr;
            BlurBuffer_ = nullptr;
            BlurEffect_ = nullptr;

            TriggerResourcesRelease();
        }
    };
}

#include <indxe>
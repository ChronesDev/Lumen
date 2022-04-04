#include <lumen/ui/lui/element/element/lui_element_input.cc>

#include "lui_context.cc"

#include <indxs>

namespace Lumen::LUI
{
    fun LUIContext::SetDrawContext(const winrt::com_ptr<LUIDrawable>& value)->void
    {
        if (DrawContext_ != value)
        {
            DrawContext_ = value;
            if (value) ResourcesUpdate();
            else
                ResourcesRelease();
        }
    }

    fun LUIContext::TriggerResourcesUpdate()->void
    {
        for (var& v : ResourcesUpdateSubscribers)
        {
            if (!v.first) continue;
            if (!v.second) continue;
            v.second();
        }
    }
    fun LUIContext::TriggerResourcesRelease()->void
    {
        for (var& v : ResourcesReleaseSubscribers)
        {
            if (!v.first) continue;
            if (!v.second) continue;
            v.second();
        }
    }

    fun LUIContext::Render()->void
    {
        if (dw == nullptr) return;

        namespace d2d = ::Lumen::Render::D2D;

        if (DrawContext_ == nullptr) INDEX_THROW("DrawContext_ (dw) was nullptr.");

        d2d::CopyBitmap(DrawContext_.get(), d2d::Res::D2D1Bitmaps[d2d::CurrentBufferIndex], BackBuffer_);

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

    fun LUIContext::ResourcesUpdate()->void { TriggerResourcesUpdate(); }
    fun LUIContext::ResourcesRelease()->void
    {
        DrawContext_ = nullptr;

        BackBuffer_ = nullptr;
        BlurBuffer_ = nullptr;
        BlurEffect_ = nullptr;

        TriggerResourcesRelease();
    }

    fun LUIContext::OnElementFocused_(const IPtr<UIElement>& e)->void
    {
        // TODO: Here
        IPtr<LUIInputElement> ue = e.template DynamicAs<LUIInputElement>();
        if (!ue.IsNull)
        {
            LInputElement_ = ue.Ptr;
            HasLInputElement_ = true;
        }
        else
        {
            LInputElement_ = nullptr;
            HasLInputElement_ = false;
        }
    }
    fun LUIContext::OnElementUnfocused_()->void
    {
        // TODO: Here
        LInputElement_ = nullptr;
        HasLInputElement_ = false;
    }

    fun LUIContext::TriggerMouseMove(Vec2F to)->void
    {
        var lastTo = MPV_;
        MPV_ = to;

        if (HasFocusedElement && !HasLInputElement) return;

        var e = ElementHitTest(to);
        var le = e.DynamicAs<LUIInputElement>();

        IPtr<LUIInputElement> lastHovered = nullptr;
        if (!LInputElement_LastHovered_.Expired) lastHovered = LInputElement_LastHovered_.Lock;

        if (le && le == lastHovered)
        {
            lastHovered->LUIContext_MouseMoveInner(to);
        }
        else
        {
            if (lastHovered)
            {
                lastHovered->LUIContext_MouseMoveOut(to);
                LInputElement_LastHovered_ = {};
            }

            if (le) { le->LUIContext_MouseMoveIn(to); }
            LInputElement_LastHovered_ = le;
        }
    }

    fun LUIContext::TriggerKeyPressed(LUIContext::TKey key)->void
    {
        if (HasFocusedElement && !HasLInputElement) return;

        var hasCaptured = false;

        IPtr<LUIInputElement> lastHovered = nullptr;
        if (!LInputElement_LastHovered_.Expired) lastHovered = LInputElement_LastHovered_.Lock;

        if (HasLInputElement)
        {
            LInputElement_->LUIContext_InnerKeyPressed(key, MPV_);
            hasCaptured = true;
        }
        elif (lastHovered)
        {
            if (lastHovered->WantsCaptureInput_)
            {
                // lastHovered->LUIContext_CaptureInput();
                lastHovered->LUIContext_InnerKeyPressed(key, MPV_);
                // LInputElement_CapturesInput_ = lastHovered;
                hasCaptured = true;
            }
        }

        HasCapturedInput_ = hasCaptured;
    }
    fun LUIContext::TriggerKeyReleased(LUIContext::TKey key)->void
    {
        if (HasFocusedElement && !HasLInputElement) return;

        var hasCaptured = false;

        IPtr<LUIInputElement> lastHovered = nullptr;
        if (!LInputElement_LastHovered_.Expired) lastHovered = LInputElement_LastHovered_.Lock;

        if (HasLInputElement)
        {
            LInputElement_->LUIContext_InnerKeyReleased(key, MPV_);
            hasCaptured = true;
        }
        elif (lastHovered)
        {
            if (lastHovered->WantsCaptureInput_)
            {
                // lastHovered->LUIContext_CaptureInput();
                lastHovered->LUIContext_InnerKeyReleased(key, MPV_);
                // LInputElement_CapturesInput_ = lastHovered;
                hasCaptured = true;
            }
        }

        HasCapturedInput_ = hasCaptured;
    }

}

#include <indxe>
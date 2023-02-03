#pragma once

#include <lumen/render/renderer/d2d/d2d.cc>
#include <lumen/ui/lui/common/common.cc>

#include "lui_descriptor.cc"

#include <indxs>

namespace Lumen::LUI
{
    struct LUIInputElement;

    struct LUIContext : virtual UIInputContext<LUIInputDescriptor>
    {
        using TKey = LUIInputDescriptor::TKey;
        using TKeyState = LUIInputDescriptor::TKeyState;

    protected:
        winrt::com_ptr<LUIDrawable> DrawContext_;

    public:
        fun SetDrawContext(const winrt::com_ptr<LUIDrawable>& value)->void;

    public:
        fun GetDrawContext() const->LUIDrawable* { return DrawContext_.get(); }
        INDEX_Property(get = GetDrawContext) LUIDrawable* dw;

    protected:
        fun TriggerResourcesUpdate()->void;
        fun TriggerResourcesRelease()->void;

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
        fun Render()->void override;

    public:
        fun ResourcesUpdate()->void;
        fun ResourcesRelease()->void;

    protected:
        LUIInputElement* LInputElement_ {};
        bool HasLInputElement_ = false;

    public:
        fun GetLInputElement()->LUIInputElement*
        {
            if (!LInputElement_) INDEX_THROW("LInputElement_ was nullptr.");
            return LInputElement_;
        }
        INDEX_Property(get = GetLInputElement) LUIInputElement* LInputElement;

        fun GetHasLInputElement() const->bool { return HasLInputElement_; }
        INDEX_Property(get = GetHasLInputElement) bool HasLInputElement;

    protected:
        fun OnElementFocused_(const IPtr<UIElement>& e)->void override;
        fun OnElementUnfocused_()->void override;

    public:
        Vec2F MPV_ {};
        std::array<TKeyState, 255> KeyMap_;

    public:
        fun GetMPV() const->const Vec2F& { return MPV_; }
        INDEX_Property(get = GetMPV) const Vec2F& MPV;

        fun IsMPVIn(Rect r) const->bool { return r.IsPointInside(MPV_); };

    public:
        fun IsKeyPressed(TKey key) const->bool { return KeyMap_[(int)key] == TKeyState::Pressed; }
        fun IsKeyReleased(TKey key) const->bool { return KeyMap_[(int)key] == TKeyState::Released; }
        fun GetKeyState(TKey key) const->TKeyState { return KeyMap_[(int)key]; }

    protected:
        WPtr<LUIInputElement> LInputElement_LastHovered_;
        // WPtr<LUIInputElement> LInputElement_CapturesInput_;

    protected:
        bool HasCapturedInput_ = false;

    public:
        fun GetHasCapturedInput() const->bool { return HasCapturedInput_; }
        INDEX_Property(get = GetHasCapturedInput) bool HasCapturedInput;

    public:
        fun TriggerMouseMove(Vec2F to)->void;
        fun TriggerKeyPressed(TKey key)->void;
        fun TriggerKeyReleased(TKey key)->void;
    };
}

#include <indxe>
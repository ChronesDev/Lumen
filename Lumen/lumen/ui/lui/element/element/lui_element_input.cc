#pragma once

#include "lui_element.cc"

#include <indxs>

namespace Lumen::LUI
{
    struct LUIInputElement : virtual LUIElement, virtual UIInputElement<LUIInputDescriptor>
    {
        using TKey = LUIInputDescriptor::TKey;
        using TKeyState = LUIInputDescriptor::TKeyState;

        friend LUIContext;

    protected:
        void OnAttachedToUIRoot_(IPtr<IUIRoot> root) override
        {
            UIInputElement_OnAttachedToUIRoot_(root);
            LUIElement_OnAttachedToUIRoot_(root);
            UIElement::OnAttachedToUIRoot_(root);
        }
        void OnDetachedFromUIRoot_() override
        {
            UIInputElement_OnDetachedFromUIRoot_();
            LUIElement_OnDetachedFromUIRoot_();
            UIElement::OnDetachedFromUIRoot_();
        }

    protected:
        bool IsHovered_ = false;

    public:
        fun GetIsHovered()const->bool { return IsHovered_; }
        INDEX_Property(get = GetIsHovered) bool IsHovered;

    protected:
        fun LUIContext_MouseMoveIn(Vec2F to)->void
        {
            IsHovered_ = true;
            OnMouseMoveIn(to);
        }
        fun LUIContext_MouseMoveInner(Vec2F at)->void { OnMouseMoveInner(at); }
        fun LUIContext_MouseMoveOut(Vec2F to)->void
        {
            IsHovered_ = false;
            OnMouseMoveOut(to);
        }

    protected:
        virtual fun OnMouseMoveIn(Vec2F to)->void { }
        virtual fun OnMouseMoveInner(Vec2F at)->void { }
        virtual fun OnMouseMoveOut(Vec2F to)->void { }

    protected:
        bool WantsCaptureInput_ = false;

        fun LUIContext_InnerKeyPressed(TKey key, Vec2F at)->void { OnInnerKeyPressed(key, at); }
        fun LUIContext_InnerKeyReleased(TKey key, Vec2F at)->void { OnInnerKeyReleased(key, at); }

    protected:
        virtual fun OnInnerKeyPressed(TKey key, Vec2F at)->void { }
        virtual fun OnInnerKeyReleased(TKey key, Vec2F at)->void { }
    };
}

#include <indxe>
#pragma once

#include "lui_element_input.cc"
#include "lui_element_selectable.cc"

#include <indxs>

namespace Lumen::LUI
{
    struct LUIButton : virtual LUIInputElement, virtual LUISelectable
    {
    public:
        LUIButton() { IsHitTestVisible_ = true; }

    public:
        fun GetIsFocusable() const->bool override { return true; }

    protected:
        bool IsPressed_ = false;

    public:
        fun GetIsPressed() const->bool { return IsPressed_; }
        INDEX_Property(get = GetIsPressed) bool IsPressed;

    protected:
        fun LUIButton_OnSelect()->void { WantsCaptureInput_ = true; }
        fun LUIButton_OnDeselect()->void { WantsCaptureInput_ = false; }

    protected:
        fun LUIButton_OnMouseMoveIn(Vec2F to)->void { IsSelected = true; }
        fun LUIButton_OnMouseMoveOut(Vec2F to)->void
        {
            if (IsFocused) Unfocus();
            IsSelected = false;
            IsPressed_ = false;
        }
        fun LUIButton_OnInnerKeyPressed(TKey key, Vec2F at)->void
        {
            if (key != Key::LeftButton) return;
            if (!IsSelected) return;

            if (HasIInputContext)
            {
                if (!IInputContext_->HasFocusedElement)
                {
                    Focus();
                    IsPressed_ = true;
                    OnButtonPressed();
                }
            }
        }
        fun LUIButton_OnInnerKeyReleased(TKey key, Vec2F at)->void
        {
            if (key != Key::LeftButton) return;

            if (!IsPressed) return;
            IsPressed_ = false;

            if (IsSelected) OnClicked();
            OnButtonReleased();
            if (IsFocused) Unfocus();
        }

    protected:
        fun OnSelect()->void override { LUIButton_OnSelect(); }
        fun OnDeselect()->void override { LUIButton_OnDeselect(); }

    protected:
        fun OnMouseMoveIn(Vec2F to)->void override { LUIButton_OnMouseMoveIn(to); }
        fun OnMouseMoveOut(Vec2F to)->void override { LUIButton_OnMouseMoveOut(to); }
        fun OnInnerKeyPressed(TKey key, Vec2F at)->void override { LUIButton_OnInnerKeyPressed(key, at); }
        fun OnInnerKeyReleased(TKey key, Vec2F at)->void override { LUIButton_OnInnerKeyReleased(key, at); }

    protected:
        virtual fun OnClicked()->void { }
        virtual fun OnButtonPressed()->void { }
        virtual fun OnButtonReleased()->void { }
    };
}

#include <indxe>
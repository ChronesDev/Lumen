#pragma once

#include "lui_element.cc"

#include <indxs>

namespace Lumen::LUI
{
    struct LUISelectable : virtual UIElement
    {
    protected:
        bool IsSelected_ = false;

    public:
        fun GetIsSelected() const->bool { return IsSelected_; }
        fun SetIsSelected(bool value)->void
        {
            if (value == IsSelected_) return;
            IsSelected_ = value;
            if (value) OnSelect();
            else
                OnDeselect();
        }
        INDEX_Property(get = GetIsSelected, put = SetIsSelected) bool IsSelected;

    protected:
        virtual fun OnSelect()->void {};
        virtual fun OnDeselect()->void {};
    };
}

#include <indxe>
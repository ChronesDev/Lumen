#pragma once

#include "lui_resource.cc"

#include <indxs>

namespace Lumen::LUI
{
    struct ColorBrushResource : LUIResource<Color, winrt::com_ptr<ID2D1SolidColorBrush>>
    {
        virtual ~ColorBrushResource() = default;

    public:
        fun GetHasResource() const->bool override { return Resource_.HasValue && Resource_; }

    public:
        fun OnUpdate()->void override
        {
            if (!lc)
            {
                Release();
                return;
            }
        }

        fun OnRelease()->void override { Resource = {}; }
    };
}

#include <indxe>
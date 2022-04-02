#pragma once

#include <lumen/log/log.cc>

#include "lui_resource.cc"

#include <indxs>

namespace Lumen::LUI
{
    struct ColorBrushResource : LUIResource<Color, winrt::com_ptr<ID2D1SolidColorBrush>>
    {
        virtual ~ColorBrushResource() = default;

    public:
        fun GetHasResource() const->bool override { return Resource_.HasValue && Resource_.has_value(); }

    public:
        fun OnUpdate()->void override
        {
            var d = lc->dw;
            if (!d) return;

            Resource_ = nullptr;
            d->CreateSolidColorBrush(ToD2DColor(Value_), Resource_->put());
        }

        fun OnRelease()->void override
        {
            Resource_ = Null;
        }
    };
}

#include <indxe>
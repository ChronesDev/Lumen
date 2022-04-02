#pragma once

#include <winrt/base.h>

#include <indx-ui>
#include <indx>

#include <lumen/ext/d2d/d2d.cc>

#include <indxs-ui>
#include <indxs>

namespace Lumen::LUI
{
    using LUIDrawable = ID2D1DeviceContext6;

    D2D1_SIZE_F ToD2DSizeF(Vec2F v) { return D2D1::SizeF(v.X, v.Y); }
    D2D1_RECT_F ToD2DRectF(Rect r) { return D2D1::RectF(r.X, r.Y, r.Second.X, r.Second.Y); }
}

#include <indxe-ui>
#include <indxe>
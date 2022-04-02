#pragma once

#include <winrt/base.h>

#include <indx-ui>
#include <indx>

#include <lumen/ext/d2d/d2d.cc>

#include <indxs>

namespace Lumen::LUI
{
    using LUIDrawable = ID2D1DeviceContext6;

    global fun ToD2DSizeF(Vec2F v)->D2D1_SIZE_F { return D2D1::SizeF(v.X, v.Y); }
    global fun ToD2DRectF(Rect r)->D2D1_RECT_F { return D2D1::RectF(r.X, r.Y, r.Second.X, r.Second.Y); }
    global fun ToD2DColor(Color c)->D2D1_COLOR_F { return D2D1::ColorF(c.R, c.G, c.B, c.A); }
}

#include <indxe>
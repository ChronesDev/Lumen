#pragma once

#include <indx>

#include "d2d.d3d12.cc"
#include "d2d.dxgi.cc"
#include "d2d.helper.cc"
#include "d2d.resources.cc"

#include <indxs>

namespace Lumen::Render::D2D
{
    fun HasInit()->bool;
    fun Init()->void;
    fun Deinit()->void;

    global Event<void()> DXRender;
    global Event<void()> DXRenderCompleted;
    global Event<void()> DXRenderInit;
    global Event<void()> DXRelease;
}

#include <indxe>
#pragma once

#include <indx>

#include "render_type.cc"
#include "renderer/renderers.cc"

#include <indxs>

namespace Lumen::Render
{
    fun Init(RenderType type)->void;
    fun Deinit()->void;
    fun TryDeinit()->void;
}

#include <indxe>
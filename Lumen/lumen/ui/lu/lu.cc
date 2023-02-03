#pragma once

#include <indx-ui>

#include <indxs>
#include <indxs-ui>

namespace Lumen::LUI { }

namespace Lumen::UI
{
    using namespace Lumen::LUI;

    fun Init()->void;
    fun Deinit()->void;

    fun InitInput()->void;
    fun DeinitInput()->void;

    fun OnInitRender()->void;
    fun OnRender()->void;
    fun OnRelease()->void;

    fun GetUI()->ui_ref;
}

#include <indxe-ui>
#include <indxe>
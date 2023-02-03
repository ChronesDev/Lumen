#pragma once

#include <kiero2>
#include <indx>

#include <indxs>

namespace Lumen::Ext::Kiero
{
    [[maybe_unused]] fun HasInit()->bool;
    fun Init(kiero::RenderType::Enum renderType)->void;
    fun Deinit()->void;
}

#include <indxe>
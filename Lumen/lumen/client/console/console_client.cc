#pragma once

#include <indxs>

namespace Lumen::Terminal
{
    global bool ShouldEject = false;

    fun ConsoleEntry()->void;
    fun PrintTitle()->void;
    fun ConsoleVersionCheckPrompt()->void;
}

#include <indxe>
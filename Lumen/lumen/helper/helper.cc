#pragma once

#include <indx>

#include <indxs>

namespace Lumen::Helper
{
    fun TryMakeConsole()->void;
    fun MakeConsole()->void;
    fun DestroyConsole()->void;
    fun StdCoutConsoleInit()->void;
    fun StdCoutConsoleDeinit()->void;
    fun EnableConsoleAnsiCodes()->void;
    fun ConfigureConsoleStyle()->void;

    fun WaitUntilGameIsLoaded()->void;

    fun SetClipboard(string text)->void;
    fun GetClipboard()->string;
}

#include <indxe>
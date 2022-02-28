#pragma once

#include <lumen/client/console/console_client.cc>
#include <lumen/log/log.cc>

#include <indxs>

namespace Lumen::Terminal::Commands
{
    global fun ExecuteClear(string command, List<string> args)->void
    {
        Log.Clear();

        PrintTitle();
        Log.Success("Cleared!");
        Debug.WriteLine();
    }
}

#include <indxe>
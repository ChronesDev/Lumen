#pragma once

#include <lumen/client/console/console_client.cc>
#include <lumen/log/log.cc>

#include <indxs>

namespace Lumen::Terminal::Commands
{
    global fun ExecuteClear(string command, List<string> args)->void
    {
        using namespace rang;

        if (args.Length == 1 && args[0] == "help")
        {
            Log.Custom(fgB::green, "clear", "\t\t", fg::blue, "");
            return;
        }

        Log.Clear();

        PrintTitle();
        Log.Success("Cleared!");
        Debug.WriteLine();
    }
}

#include <indxe>
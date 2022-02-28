#pragma once

#include <lumen/client/console/console_client.cc>
#include <lumen/log/log.cc>

#include <indxs>

namespace Lumen::Terminal::Commands
{
    global fun ExecuteEject(string command, List<string> args)->void
    {
        using namespace rang;

        if (args.Length == 1 && args[0] == "help")
        {
            Log.Custom(fgB::green, "eject", "\t\t", fg::blue, "");
            return;
        }

        ShouldEject = true;

        Log.NewLine();

        Log.Custom(style::bold, fg::cyan, bg::blue, "Ejecting ^^");
        Time.Delay(TimeSpan::FromSec(0.4));
    }
}

#include <indxe>
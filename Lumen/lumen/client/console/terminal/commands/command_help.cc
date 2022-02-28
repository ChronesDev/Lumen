#pragma once

#include <lumen/log/log.cc>

#include <indxs>

namespace Lumen::Terminal::Commands
{
    global fun ExecuteHelp(string command, List<string> args)->void
    {
        using namespace rang;

        Log.NewLine();
        Log.Custom(fg::cyan, "help \t", fg::gray, " - Displays this output");
        Log.Custom(fg::cyan, "clear \t", fg::gray, " - Clears the console");
        Log.Custom(fg::cyan, "eject \t", fg::gray, " - Ejects the client");
        Log.Custom(fg::cyan, "on \t", fg::gray, " - Enables a module.");
        Log.Custom(fg::cyan, "off \t", fg::gray, " - Disables a module.");
        Log.Custom(fg::cyan, "info \t", fg::gray, " - Displays info about a module.");
        Log.NewLine();
    }
}

#include <indxe>
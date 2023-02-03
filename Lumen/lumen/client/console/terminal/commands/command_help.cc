#pragma once

#include <lumen/log/log.cc>

#include <indxs>

namespace Lumen::Terminal::Commands
{
    global fun ExecuteHelp(string command, List<string> args)->void
    {
        using namespace rang;

        Log.NewLine();
        Log.Custom(fg::cyan, "help         ", fg::gray, " - Displays this output");
        Log.Custom(fg::cyan, "clear        ", fg::gray, " - Clears the console");
        Log.Custom(fg::cyan, "eject        ", fg::gray, " - Ejects the client");
        Log.Custom(fg::cyan, "on           ", fg::gray, " - Enables a module.");
        Log.Custom(fg::cyan, "off          ", fg::gray, " - Disables a module.");
        Log.Custom(fg::cyan, "info         ", fg::gray, " - Displays info about a module.");
        Log.Custom(fg::cyan, "set          ", fg::gray, " - Sets a property from a module.");
        Log.Custom(fg::cyan, "get          ", fg::gray, " - Gets a property from a module.");
        Log.Custom(fg::cyan, "bind         ", fg::gray, " - Binds a key to a module.");
        Log.Custom(fg::cyan, "unbind       ", fg::gray, " - Unbinds a module.");
        Log.Custom(fg::cyan, "config       ", fg::gray, " - Manages configurations.");
        Log.Custom(fg::cyan, "save         ", fg::gray, " - Saves a config.");
        Log.Custom(fg::cyan, "load         ", fg::gray, " - Loads a config.");
        Log.NewLine();
    }
}

#include <indxe>
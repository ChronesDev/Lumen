#include "terminal_commands.cc"

#include "commands/command_clear.cc"
#include "commands/command_eject.cc"
#include "commands/command_help.cc"
#include "commands/command_on_off.cc"

#include <indxs>

namespace Lumen::Terminal
{
    fun ExecuteCommand(string command, List<string> args)->bool
    {
        if (command == "") return false;

        elif (command == "clear")
        {
            Commands::ExecuteClear(command, args);
            return true;
        }

        elif (command == "eject")
        {
            Commands::ExecuteEject(command, args);
            return true;
        }

        elif (command == "help")
        {
            Commands::ExecuteHelp(command, args);
            return true;
        }

        elif (command == "on")
        {
            Commands::ExecuteOn(command, args);
            return true;
        }

        elif (command == "off")
        {
            Commands::ExecuteOff(command, args);
            return true;
        }

        else return false;
    }
}

#include <indxe>
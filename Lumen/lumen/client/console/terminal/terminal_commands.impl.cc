#include "terminal_commands.cc"

#include "commands/command_bind_unbind.cc"
#include "commands/command_clear.cc"
#include "commands/command_eject.cc"
#include "commands/command_get_set.cc"
#include "commands/command_help.cc"
#include "commands/command_info.cc"
#include "commands/command_on_off.cc"
#include "commands/command_save_load.cc"

#include <indxs>

namespace Lumen::Terminal
{
    fun ExecuteCommand(string command, List<string> args)->bool
    {
        if (command == "") return false;

        elif (command == "bind")
        {
            Commands::ExecuteBind(command, args);
            return true;
        }

        elif (command == "unbind")
        {
            Commands::ExecuteUnbind(command, args);
            return true;
        }

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

        elif (command == "get")
        {
            Commands::ExecuteGet(command, args);
            return true;
        }

        elif (command == "set")
        {
            Commands::ExecuteSet(command, args);
            return true;
        }

        elif (command == "help")
        {
            Commands::ExecuteHelp(command, args);
            return true;
        }

        elif (command == "info")
        {
            Commands::ExecuteInfo(command, args);
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

        elif (command == "save")
        {
            Commands::ExecuteSave(command, args);
            return true;
        }

        else return false;
    }
}

#include <indxe>
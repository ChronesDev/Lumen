#pragma once

#include <lumen/log/log.cc>
#include <lumen/module/modules.cc>

#include <indxs>

namespace Lumen::Terminal::Commands
{
    global fun ExecuteOn(string command, List<string> args)->void
    {
        using namespace rang;

        if (args.Length != 1)
        {
            Log.Fail("Wrong amount of arguments.");
            Log.Custom(fgB::green, "on (module)", "\t\t", fg::blue, "Example: on zoom");
            Log.Custom(fgB::green, "on (.id)", "\t\t", fg::blue, "Example: on .lumen_zoom");
            return;
        }

        var arg = args[0];
        Module* mod = nullptr;

        if (arg.StarsWith("."))
        {
            var id = arg.SubString(1, arg.Length - 1);
            var result = Modules::TryFindModuleById(id);
            if (result.HasValue) mod = result->Ptr;
            else
            {
                Log.Fail("A module with the id ", id, " wasn't found.");
                return;
            }
        }

        else
        {
            var name = arg;
            var result = Modules::TryFindModuleByNameAnyCase(name);
            if (result.HasValue) mod = result->Ptr;
            else
            {
                Log.Fail("A module by the name ", name, " wasn't found.");
                return;
            }
        }

        if (!mod->HasState)
        {
            Log.Custom(mod->Name, " cannot be toggled.");
            return;
        }

        if (mod->IsEnabled)
        {
            Log.Custom(mod->Name, " is already enabled.");
            return;
        }

        try
        {
            if (mod->IsDisabled) mod->Enable();
        }
        catch (std::exception ex)
        {
            Log.Fail(mod->Name, " throwed an exception while trying to enable it.");
        }

        Log.Success("Enabled ", mod->Name);
    }

    global fun ExecuteOff(string command, List<string> args)->void
    {
        using namespace rang;

        if (args.Length != 1)
        {
            Log.Fail("Wrong amount of arguments.");
            Log.Custom(fgB::green, "on (module)", "\t\t", fg::blue, "Example: on zoom");
            Log.Custom(fgB::green, "on (.id)", "\t\t", fg::blue, "Example: on .lumen_zoom");
            return;
        }

        var arg = args[0];
        Module* mod = nullptr;

        if (arg.StarsWith("."))
        {
            var id = arg.SubString(1, arg.Length - 1);
            var result = Modules::TryFindModuleById(id);
            if (result.HasValue) mod = result->Ptr;
            else
            {
                Log.Fail("A module with the id ", id, " wasn't found.");
                return;
            }
        }

        else
        {
            var name = arg;
            var result = Modules::TryFindModuleByNameAnyCase(name);
            if (result.HasValue) mod = result->Ptr;
            else
            {
                Log.Fail("A module by the name ", name, " wasn't found.");
                return;
            }
        }

        if (!mod->HasState)
        {
            Log.Custom(mod->Name, " cannot be toggled.");
            return;
        }

        if (mod->IsDisabled)
        {
            Log.Custom(mod->Name, " is already disabled.");
            return;
        }

        try
        {
            if (mod->IsEnabled) mod->Disable();
        }
        catch (std::exception ex)
        {
            Log.Fail(mod->Name, " throwed an exception while trying to disable it.");
        }

        Log.Success("Disabled ", mod->Name);
    }
}

#include <indxe>
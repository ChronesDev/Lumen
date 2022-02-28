#pragma once

#include <lumen/log/log.cc>
#include <lumen/module/modules.cc>

#include <indxs>

namespace Lumen::Terminal::Commands
{
    global fun ExecuteInfo(string command, List<string> args)->void
    {
        using namespace rang;

        if (args.Length == 1 && args[0] == "help")
        {
            Log.Custom(fgB::green, "info (module)", "\t\t", fg::blue, "Example: info zoom");
            Log.Custom(fgB::green, "info (.id)", "\t\t", fg::blue, "Example: info .lumen_zoom");
            return;
        }

        if (args.Length != 1)
        {
            Log.Fail("Wrong amount of arguments.");
            Log.Custom(fgB::green, "info (module)", "\t\t", fg::blue, "Example: info zoom");
            Log.Custom(fgB::green, "info (.id)", "\t\t", fg::blue, "Example: info .lumen_zoom");
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
                Log.Fail("A module by the id ", id, " wasn't found.");
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

        try
        {
            var name = mod->Name;
            var id = mod->Id;
            var description = mod->Description;
            var hasState = mod->HasState;
            var enabled = false;

            if (hasState) enabled = mod->IsEnabled;

            Log.NewLine();
            Log.Custom(fg::reset, "Module: ", fgB::green, name, fg::blue, " (", fgB::blue, ".", fgB::cyan, id, fg::blue, ")");
            Log.Custom(fg::reset, "Description: ", fgB::blue, description);
            Log.Custom(fg::reset, "HasState: ", fgB::blue, hasState ? "true" : "false");
            if (hasState) Log.Custom(fg::reset, "Enabled: ", fgB::blue, enabled ? "true" : "false");
            Log.NewLine();
        }
        catch (std::exception ex)
        {
            Log.Fail(fg::black, bgB::red, mod->Name, " throwed an exception while trying to gather info: ", fgB::red,
                bg::reset, "\n\t", ex.what());
            return;
        }
    }
}

#include <indxe>
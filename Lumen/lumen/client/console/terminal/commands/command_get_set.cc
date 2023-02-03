#pragma once

#include <lumen/log/log.cc>
#include <lumen/module/modules.cc>

#include <indxs>

namespace Lumen::Terminal::Commands
{
    global fun ExecuteGet(string command, List<string> args)->void
    {
        using namespace rang;

        if (args.Length == 1 && args[0] == "help")
        {
            Log.Custom(fgB::green, "set (module) (...)", "\t\t", fg::blue, "Example: set zoom to 30");
            Log.Custom(fgB::green, "set (.id) (...)", "\t\t", fg::blue, "Example: set .lumen_zoom duration 0.2");
            return;
        }

        if (args.Length < 2)
        {
            Log.Fail("To few arguments.");
            Log.Custom(fgB::green, "set (module) (...)", "\t\t", fg::blue, "Example: set zoom to 30");
            Log.Custom(fgB::green, "set (.id) (...)", "\t\t", fg::blue, "Example: set .lumen_zoom duration 0.2");
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
            args.Erase(args.begin());
            mod->ExecuteGet(args);
        }
        catch (std::exception ex)
        {
            Log.Fail(fg::black, bgB::red, mod->Name, " throwed an exception while trying to execute set: ", fgB::red,
                bg::reset, "\n\t", ex.what());
            return;
        }
    }

    global fun ExecuteSet(string command, List<string> args)->void
    {
        using namespace rang;

        if (args.Length == 1 && args[0] == "help")
        {
            Log.Custom(fgB::green, "set (module) (...)", "\t\t", fg::blue, "Example: set zoom to 30");
            Log.Custom(fgB::green, "set (.id) (...)", "\t\t", fg::blue, "Example: set .lumen_zoom duration 0.2");
            return;
        }

        if (args.Length < 2)
        {
            Log.Fail("To few arguments.");
            Log.Custom(fgB::green, "set (module) (...)", "\t\t", fg::blue, "Example: set zoom to 30");
            Log.Custom(fgB::green, "set (.id) (...)", "\t\t", fg::blue, "Example: set .lumen_zoom duration 0.2");
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
            args.Erase(args.begin());
            mod->ExecuteSet(args);
        }
        catch (std::exception ex)
        {
            Log.Fail(fg::black, bgB::red, mod->Name, " throwed an exception while trying to execute set: ", fgB::red,
                bg::reset, "\n\t", ex.what());
            return;
        }
    }
}

#include <indxe>
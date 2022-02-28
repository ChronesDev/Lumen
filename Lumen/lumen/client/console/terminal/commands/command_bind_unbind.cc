#pragma once

#include <lumen/log/log.cc>
#include <lumen/input/input.cc>
#include <lumen/module/modules.cc>

#include <indxs>

namespace Lumen::Terminal::Commands
{
    global fun ExecuteBind(string command, List<string> args)->void
    {
        using namespace rang;

        if (args.Length == 1 && args[0] == "help")
        {
            Log.Custom(fgB::green, "bind (module) (key)", "\t\t", fg::blue, "Example: bind zoom x");
            Log.Custom(fgB::green, "bind (.id) (key)", "\t\t", fg::blue, "Example: bind .lumen_zoom x");
            return;
        }

        if (args.Length != 2)
        {
            Log.Fail("Wrong amount of arguments.");
            Log.Custom(fgB::green, "bind (module) (key)", "\t\t", fg::blue, "Example: bind zoom x");
            Log.Custom(fgB::green, "bind (.id) (key)", "\t\t", fg::blue, "Example: bind .lumen_zoom x");
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

        var key = Input::FindKeyByKeyName(args[1]);

        if (key == Key::Null)
        {
            Log.Fail(fg::black, bgB::red, args[1], fgB::red, bg::reset, " is not a key.");
            return;
        }

        if (!mod->HasBinding)
        {
            Log.Custom(mod->Name, " cannot be bound.");
            return;
        }

        try
        {
            mod->BindTo(key);
        }
        catch (std::exception ex)
        {
            Log.Fail(fg::black, bgB::red, mod->Name, " throwed an exception while trying to bind the module: ", fgB::red,
                bg::reset, "\n\t", ex.what());
            return;
        }

        Log.Custom(fg::blue, mod->Name, " -> ", args[1]);
    }

    global fun ExecuteUnbind(string command, List<string> args)->void
    {
        using namespace rang;

        if (args.Length == 1 && args[0] == "help")
        {
            Log.Custom(fgB::green, "unbind (module)", "\t\t", fg::blue, "Example: unbind zoom");
            Log.Custom(fgB::green, "unbind (.id)", "\t\t", fg::blue, "Example: unbind .lumen_zoom");
            return;
        }

        if (args.Length != 1)
        {
            Log.Fail("Wrong amount of arguments.");
            Log.Custom(fgB::green, "unbind (module)", "\t\t", fg::blue, "Example: unbind zoom");
            Log.Custom(fgB::green, "unbind (.id)", "\t\t", fg::blue, "Example: unbind .lumen_zoom");
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

        if (!mod->HasBinding)
        {
            Log.Custom(mod->Name, " cannot be unbound.");
            return;
        }

        try
        {
            mod->Unbind();
        }
        catch (std::exception ex)
        {
            Log.Fail(fg::black, bgB::red, mod->Name, " throwed an exception while trying to unbind the module: ", fgB::red,
                bg::reset, "\n\t", ex.what());
            return;
        }

        Log.Custom(fg::blue, mod->Name, " -> unbound");
    }
}

#include <indxe>
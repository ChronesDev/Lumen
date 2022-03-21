#pragma once

#include <fstream>

#include <lumen/data/data.cc>
#include <lumen/log/log.cc>
#include <lumen/module/modules.cc>

#include <indxs>

namespace Lumen::Terminal::Commands
{
    global fun ExecuteSave(string command, List<string> args)->void
    {
        using namespace rang;

        if (args.Length == 1 && args[0] == "help")
        {
            Log.Custom(fgB::green, "save", "\t\t");
            Log.Custom(fgB::green, "save (name)", "\t\t", fg::blue, "Example: save my_config");
            return;
        }

        if (args.Length != 1)
        {
            Log.Fail("Wrong amount of arguments.");
            Log.Custom(fgB::green, "save", "\t\t");
            Log.Custom(fgB::green, "save (name)", "\t\t", fg::blue, "Example: save my_config");
            return;
        }

        try
        {
            nlohmann::json j = {};
            j["@LumenModules"] = "*";

            Modules::MakeConfig(j);
            string s = to_string(j);

            var path = Data::ConfigPath / "configs" / (std::string)args[0] / "lumen_config.lu";
            std::filesystem::create_directories(path.parent_path());

            std::ofstream ofs(path);
            ofs << s;
            ofs.close();
        }
        catch (std::exception& ex)
        {
            Log.Fail("An exception has been throwed while trying to make a config.");
        }
    }
}

#include <indxe>
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

        if (!Data::IsConfigNameValid(args[0]))
        {
            Log.Fail("Invalid config name. Try to only use Alphabetic and Numeric characters.");
            return;
        }

        try
        {
            nlohmann::json j = Data::MakeConfigData();
            string s = to_string(j);

            var path = Data::ConfigPath / "configs" / (std::string)args[0] / "lumen_config.lu";
            std::filesystem::create_directories(path.parent_path());

            if (std::filesystem::exists(path))
            {
                Log.Custom(fgB::magenta, "A config with the same name has been found.");
                Console.Write(fgB::yellow, " Still continue? ", fg::gray, "(", fgB::green, "Y", fg::gray, "/",
                    fgB::red, "N", fg::gray, ") ", fgB::cyan, "-> ");

                var key = getchar();
                getchar();

                if (key != 'y' && key != 'Y')
                {
                    Log.Custom("Cancelled.");
                    return;
                }

                std::filesystem::remove(path);
            }

            std::ofstream ofs(path);
            ofs << s;
            ofs.close();
        }
        catch (std::exception& ex)
        {
            Log.Fail("An exception has been throwed while trying to make a config.");
        }
    }

    global fun ExecuteLoad(string command, List<string> args)->void
    {
        using namespace rang;

        if (args.Length == 1 && args[0] == "help")
        {
            Log.Custom(fgB::green, "load", "\t\t");
            Log.Custom(fgB::green, "load (name)", "\t\t", fg::blue, "Example: load my_config");
            return;
        }

        if (args.Length != 1)
        {
            Log.Fail("Wrong amount of arguments.");
            Log.Custom(fgB::green, "load", "\t\t");
            Log.Custom(fgB::green, "load (name)", "\t\t", fg::blue, "Example: load my_config");
            return;
        }

        if (!Data::IsConfigNameValid(args[0]))
        {
            Log.Fail("Invalid config name. Try to only use Alphabetic and Numeric characters.");
            return;
        }

        try
        {
            var path = Data::ConfigPath / "configs" / (std::string)args[0] / "lumen_config.lu";
            if (!std::filesystem::exists(path))
            {
                Log.Fail("Could not find the config by the name ", style::reversed, args[0], style::reset, ".");
                return;
            }

            std::ifstream ifs(path);
            SS ss;
            ss << ifs.rdbuf();
            var s = ss.Make();

            var j = nlohmann::json::parse(s);
            Data::LoadConfigData(j);

            {
                string name = j["Name"];
                string author = j["Author"];
                author = author.empty() ? "?" : author;
                Version target = Version::Parse(j["Target"]);

                Log.NewLine();
                //Log.Custom(fgB::green, name, fg::blue, " (by ", fgB::cyan, author, fg::blue, ")");
                //Log.Custom(fg::reset, "Description: ", fgB::blue, description);
                //Log.Custom(fg::reset, "HasState: ", fgB::blue, hasState ? "true" : "false");
                //if (hasState) Log.Custom(fg::reset, "Enabled: ", fgB::blue, enabled ? "true" : "false");
                Log.NewLine();
            }
        }
        catch (std::exception& ex)
        {
            Log.Fail("An exception has been throwed while trying to load a config.");
            Log.Fail(fg::red, "\t", ex.what());
        }
    }
}

#include <indxe>
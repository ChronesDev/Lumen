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
            nlohmann::json j = Data::MakeConfigData(args[0]);
            string s = to_string(j);

            var path = Data::ConfigPath / "configs" / (std::string)args[0] / "lumen_config.lu";

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

            std::filesystem::create_directories(path.parent_path());

            std::ofstream ofs(path);
            ofs << s;
            ofs.close();
        }
        catch (std::runtime_error& ex)
        {
            Log.Fail("An exception has been throwed while trying to make a config.");
            Log.Fail(fg::red, "\t", ex.what());
            return;
        }
        catch (std::exception& ex)
        {
            Log.Fail("An exception has been throwed while trying to make a config.");
            Log.Fail(fg::red, "\t", ex.what());
            return;
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
                string name = (std::string)j["Name"];
                string author = (std::string)j["Author"];
                author = author.empty() ? "?" : author;
                Version target = Version::Parse((std::string)j["Target"]);

                Log.NewLine();

                /*
                 * |     __                                  ______            _____       |
                 * |    / /   __  ______ ___  ___  ____     / ____/___  ____  / __(_)___ _ |
                 * |   / /   / / / / __ `__ \/ _ \/ __ \   / /   / __ \/ __ \/ /_/ / __ `/ |
                 * |  / /___/ /_/ / / / / / /  __/ / / /  / /___/ /_/ / / / / __/ / /_/ /  |
                 * | /_____/\__,_/_/ /_/ /_/\___/_/ /_/   \____/\____/_/ /_/_/ /_/\__, /   |
                 * |                                                             /____/    |
                 */

                /*
                 * |    ______            _____       |
                 * |   / ____/___  ____  / __(_)___ _ |
                 * |  / /   / __ \/ __ \/ /_/ / __ `/ |
                 * | / /___/ /_/ / / / / __/ / /_/ /  |
                 * | \____/\____/_/ /_/_/ /_/\__, /   |
                 * |                        /____/    |
                 */

                Console.WriteLine(fgB::yellow, R"(    ______            _____       )");
                Console.WriteLine(fgB::yellow, R"(   / ____/___  ____  / __(_)___ _ )");
                Console.WriteLine(fgB::yellow, R"(  / /   / __ \/ __ \/ /_/ / __ `/ )");
                Console.WriteLine(fgB::yellow, R"( / /___/ /_/ / / / / __/ / /_/ /  )");
                Console.WriteLine(fgB::yellow, R"( \____/\____/_/ /_/_/ /_/\__, /   )");
                Console.WriteLine(fgB::yellow, R"(                        /____/    )");

                Console.Write(" ");
                if (author == "?") Console.WriteLine(fgB::cyan, name, fg::reset);
                else
                    Console.WriteLine(fgB::cyan, name, fg::blue, " (by ", fg::cyan, author, fg::blue, ")");

                Log.NewLine();

                Log.Success(fgB::green, "Successfully loaded ", fgB::cyan, name, fgB::green, ".");
            }
        }
        catch (std::runtime_error& ex)
        {
            Log.Fail("An exception has been throwed while trying to load a config.");
            Log.Fail(fg::red, "\t", ex.what());
            return;
        }
        catch (std::exception& ex)
        {
            Log.Fail("An exception has been throwed while trying to load a config.");
            Log.Fail(fg::red, "\t", ex.what());
            return;
        }
    }
}

#include <indxe>
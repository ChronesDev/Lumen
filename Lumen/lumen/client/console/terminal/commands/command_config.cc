#pragma once

#include <fstream>

#include <lumen/data/data.cc>
#include <lumen/helper/helper.cc>
#include <lumen/log/log.cc>
#include <lumen/module/modules.cc>

#include <indxs>

namespace Lumen::Terminal::Commands
{
    global fun ExecuteConfig(string command, List<string> args)->void
    {
        using namespace rang;

        if (args.Length == 1 && args[0] == "help")
        {
            Log.Custom(fgB::green, "config", "\t\t");
            Log.Custom(fgB::green, "config list", "\t\t");
            Log.Custom(fgB::green, "config import", "\t\t");
            Log.Custom(
                fgB::green, "config export (config name)", "\t\t", fg::blue, "Example: config export my_config");
            return;
        }

        if (args.Length == 0)
        {
            Log.Fail("Wrong amount of arguments.");
            Log.Custom(fgB::green, "config", "\t\t");
            Log.Custom(fgB::green, "config list", "\t\t");
            Log.Custom(fgB::green, "config import", "\t\t");
            Log.Custom(
                fgB::green, "config export (config name)", "\t\t", fg::blue, "Example: config export my_config");
            return;
        }

        if (args.Length == 1 && args[0] == "list")
        {
            if (args.Length != 1)
            {
                Log.Fail("Wrong amount of arguments.");
                return;
            }

            return;
        }

        if (args[0] == "import")
        {
            if (args.Length != 1)
            {
                Log.Fail("Wrong amount of arguments.");
                return;
            }

            string i;
            try
            {
                i = Helper::GetClipboard();
                if (i == "")
                {
                    Log.Fail("Invalid config in Clipboard.");
                    return;
                }
            }
            catch (...)
            {
                Log.Fail("An exception was thrown while trying to read the clipboard.");
                return;
            }

            if (!i.contains("@LumenConfig"))
            {
                Log.Fail("Invalid data.");
                return;
            }

            nlohmann::json j = {};

            {
                try
                {
                    j = nlohmann::json::parse(i);
                }
                catch (std::exception& ex)
                {
                    Log.Fail("An exception was thrown while trying to parse the imported data.");
                    Log.Fail(fg::red, "\t", ex.what());
                    return;
                }

                try
                {
                    Data::CheckConfig(j);
                }
                catch (std::runtime_error& ex)
                {
                    Log.Fail("Invalid config.");
                    Log.Fail(fg::red, "\t", ex.what());
                    return;
                }

                try
                {
                    Data::LoadConfigData(j);
                }
                catch (std::runtime_error& ex)
                {
                    Log.Fail("An exception was thrown while trying to load the config.");
                    Log.Fail(fg::red, "\t", ex.what());
                    return;
                }
                catch (std::exception& ex)
                {
                    Log.Fail("An exception was thrown while trying to load the config.");
                    Log.Fail(fg::red, "\t", ex.what());
                    return;
                }
            }

            {
                string name = (std::string)j["Name"];
                string author = (std::string)j["Author"];
                author = author.empty() ? "?" : author;
                Version target = Version::Parse((std::string)j["Target"]);

                Log.NewLine();

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

            return;
        }

        if (args[0] == "export")
        {
            if (args.Length != 2)
            {
                Log.Fail("Wrong amount of arguments.");
                return;
            }

            string s;
            try
            {
                nlohmann::json j = Data::MakeConfigData(args[1]);
                string s = to_string(j);
            }
            catch (std::runtime_error& ex)
            {
                Log.Fail("An exception was thrown while trying to make a config.");
                Log.Fail(fg::red, "\t", ex.what());
                return;
            }
            catch (std::exception& ex)
            {
                Log.Fail("An exception was thrown while trying to make a config.");
                Log.Fail(fg::red, "\t", ex.what());
                return;
            }

            try
            {
                Helper::SetClipboard(s);
            }
            catch (...)
            {
                Log.Fail("An exception was thrown while trying to write to the clipboard.");
                return;
            }

            return;
        }
    }
}

#include <indxe>
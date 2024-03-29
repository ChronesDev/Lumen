#include "console_client.cc"

#include "package/package.cc"

#include <lumen/config/config.cc>
#include <lumen/data/data.cc>
#include <lumen/detour/detour.cc>
#include <lumen/helper/helper.cc>
#include <lumen/input/input.cc>
#include <lumen/log/log.cc>
#include <lumen/module/modules.cc>

#include <lumen/module/modules/module_fullbright.cc>
#include <lumen/module/modules/module_night.cc>
#include <lumen/module/modules/module_timechanger.cc>
#include <lumen/module/modules/module_zoom.cc>

#include <lumen/render/render.cc>

// TODO: !!!
#include <lumen/ui/lu/lu.cc>

#include "terminal/terminal_parser.cc"

#include <indxs>

namespace Lumen::Terminal
{
    fun PreConsoleInit_()->void;
    fun PostConsoleDeinit_()->void;

    fun ConsoleEntry()->void
    {
        using namespace rang;

        PrintTitle();

        Log(fgB::gray, "Waiting until Minecraft fully loaded...");

        Helper::WaitUntilGameIsLoaded();

        Log.GoToLastLine();
        Log.DelLine();
        Log.Success("Loaded!");
        Log.NewLine();

        // ConsoleVersionCheckPrompt()
        {
            try
            {
                ConsoleVersionCheckPrompt();
            }
            catch (...)
            {
                goto jmp_return;
            }
        }

        // PreConsoleInit_()
        {
            try
            {
                PreConsoleInit_();
            }
            catch (...)
            {
                goto jmp_deinit;
            }
        }

        Log.Clear();
        PrintTitle();

        Log.Success("Done!");
        Log.NewLine();

        Log.Custom("Use help to display all commands.");

        while (true)
        {
            ProcessCommand(Log.TerminalInput());
            if (ShouldEject) break;
        }

    jmp_deinit:
        PostConsoleDeinit_();
    jmp_return:
        return;
    }

    fun PrintTitle()->void
    {
        using namespace rang;

        Console.Write(style::bold);
        Console.WriteLine(R"!(  _                                 )!");
        Console.WriteLine(R"!( | |                                )!");
        Console.WriteLine(R"!( | |    _   _ _ __ ___   ___ _ __   )!");
        Console.WriteLine(R"!( | |   | | | | '_ ` _ \ / _ \ '_ \  )!");
        Console.WriteLine(R"!( | |___| |_| | | | | | |  __/ | | | )!");
        Console.WriteLine(R"!( |______\__,_|_| |_| |_|\___|_| |_| )!");
        Console.WriteLine(R"!(                                    )!");
        Console.Write(style::reset);

        //|                                    |
        //| By CXCubeHD                        |
        //| By CXCubeHD                   v0.1 |

        static string preSubPart = " By CXCubeHD                       ";
        static string postSubPart = " ";

        var version = Str("v", Config::ClientVersion.Major, ".", Config::ClientVersion.Minor);
        var subPart
            = preSubPart.SubString(0, Max<ulong>(preSubPart.Length - version.Length, 0)) + version + postSubPart;

        Console.WriteLine(fg::cyan, subPart, fg::reset);

        Log.NewLine();
    }

    fun ConsoleVersionCheckPrompt()->void
    {
        using namespace rang;

        Log("Checking version...");

        var targetVersion = Config::TargetPackageVersion;
        var currentVersion = Package::PackageVersion();

        Log("Versions: Target ", (string)targetVersion, "  Package ", (string)currentVersion);

        if (targetVersion != currentVersion)
        {
            Time.Delay(TimeSpan::FromSec(0.3));
            Log.Custom(fgB::magenta, "It looks like Lumen does not support the running Minecraft version.");

            Console.Write(fgB::yellow, " Do you still want to continue? ", fg::gray, "(", fgB::green, "Y", fg::gray, "/",
                fgB::red, "N", fg::gray, ") ", fgB::cyan, "-> ");

            var key = getchar();
            getchar();

            if (key == 'y' || key == 'Y')
            {
                // Console.WriteLine(fg::black, bgB::green, "Y", fg::reset, bg::reset);
                // Log.NewLine();
                return;
            }
            else
            {
                // Console.WriteLine(fg::black, bgB::red, "N", fg::reset, bg::reset);
                // Log.NewLine();
                Log("Ejecting in 9 seconds");
                Time.Delay(TimeSpan::FromSec(9));
                INDEX_THROW("Eject.");
            }
        }
    }

    fun PreConsoleInit_()->void
    {
        using namespace rang;

        try
        {
            Log("Initializing Data System");
            Data::Init();

            Log("Initializing MinHook");
            Detour::InitMinHook();

            Log("Initializing input hooks");
            Input::Init();

            Log("Adding modules");
            Modules::AddModule(INew<Modules::Fullbright>());
            Modules::AddModule(INew<Modules::Night>());
            Modules::AddModule(INew<Modules::TimeChanger>());
            Modules::AddModule(INew<Modules::Zoom>());

            Log("Initializing modules");
            Modules::Init();

            //Log("Initializing Renderer");
            //Lumen::Render::Init(Render::RenderType::D2D);

            //UI::Init();
        }
        catch (std::runtime_error& ex)
        {
            Log.Fail(fg::black, bgB::red, "There was an error while trying to initialize:", fgB::red, bg::reset,
                " \n\t", ex.what());
            Log.NewLine();
            Log("Ejecting in 9 seconds");
            Time.Delay(TimeSpan::FromSec(9));
            INDEX_THROW("Eject.");
        }
        catch (std::exception& ex)
        {
            Log.Fail(fg::black, bgB::red, "There was an error while trying to initialize:", fgB::red, bg::reset,
                " \n\t", ex.what());
            Log.NewLine();
            Log("Ejecting in 9 seconds");
            Time.Delay(TimeSpan::FromSec(9));
            INDEX_THROW("Eject.");
        }
    }

    fun PostConsoleDeinit_()->void
    {
        using namespace rang;

        //Lumen::Render::TryDeinit();

        Modules::Deinit();
        Input::Deinit();
        Detour::DeinitMinHook();
        Data::Deinit();
    }
}

#include <indxe>
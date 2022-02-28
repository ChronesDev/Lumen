#include "console_client.cc"

#include <lumen/detour/detour.cc>
#include <lumen/entry/entry.cc>
#include <lumen/helper/helper.cc>
#include <lumen/input/input.cc>
#include <lumen/log/log.cc>

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

        try
        {
            PreConsoleInit_();
        }
        catch (...)
        {
            goto jmp_deinit;
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
    }

    fun PrintTitle()->void
    {
        using namespace rang;

        Debug.Write(style::bold);
        Debug.WriteLine(R"!(  _                                 )!");
        Debug.WriteLine(R"!( | |                                )!");
        Debug.WriteLine(R"!( | |    _   _ _ __ ___   ___ _ __   )!");
        Debug.WriteLine(R"!( | |   | | | | '_ ` _ \ / _ \ '_ \  )!");
        Debug.WriteLine(R"!( | |___| |_| | | | | | |  __/ | | | )!");
        Debug.WriteLine(R"!( |______\__,_|_| |_| |_|\___|_| |_| )!");
        Debug.WriteLine(R"!(                                    )!");
        Debug.Write(style::reset);

        //|                                    |
        //| By CXCubeHD                   v0.1 |
        Debug.WriteLine(fg::cyan, " By CXCubeHD                   v0.1 ", fg::reset);

        Log.NewLine();
    }

    fun PreConsoleInit_()->void
    {
        using namespace rang;

        Log("Initializing input hooks");

        try
        {
            Detour::InitMinHook();
            Log("Initialized MinHook");

            Input::Init();
        }
        catch (std::exception ex)
        {
            Log.Fail(fg::black, bgB::red, "There was an error while trying to initialize hooks:", fgB::red, bg::reset,
                " \n\t", ex.what());
            Log.NewLine();
            Log("Ejecting in 9 seconds");
            Time.Delay(TimeSpan::FromSec(9));
            throw std::exception();
        }
    }

    fun PostConsoleDeinit_()->void
    {
        using namespace rang;

        Input::Deinit();
        Detour::DeinitMinHook();
    }
}

#include <indxe>
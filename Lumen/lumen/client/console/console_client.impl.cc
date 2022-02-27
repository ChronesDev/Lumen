#include "console_client.cc"

#include <lumen/helper/helper.cc>
#include <lumen/log/log.cc>

#include "terminal/terminal_parser.cc"

#include <indxs>

namespace Lumen::Terminal
{
	fun ConsoleEntry()->void
	{
		using namespace rang;

		PrintTitle();

		Log(fgB::gray, "Waiting until Minecraft fully loaded...");

		Helper::WaitUntilGameIsLoaded();

		Log.DelLine();
		Log.Success("Done!");
		Debug.WriteLine();

		Log.Custom("Use help to display all commands.");

		while (true)
		{
			ProcessCommand(Log.TerminalInput());
		}
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

		Debug.WriteLine();
	}
}

#include <indxe>
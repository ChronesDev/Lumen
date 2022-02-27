#include "entry.cc"

#include <lumen/helper/helper.cc>
#include <lumen/log/log.cc>

#include <indxs>

namespace Lumen
{
	fun Entry() -> void
	{
		using namespace rang;

		Helper::TryMakeConsole();
		Helper::EnableConsoleAnsiCodes();
		Helper::ConfigureConsoleStyle();
		SetConsoleTitle("Lumen Client");

		rang::setWinTermMode(rang::winTerm::Ansi);

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
		Log(fgB::gray, "Initializing...");
	}
}

#include <indxe>
#include "entry.cc"

#include <lumen/helper/helper.cc>

#include <indxs>

namespace Lumen
{
	fun Entry() -> void
	{
		Helper::TryMakeConsole();
		SetConsoleTitle("Lumen Client");

		Debug.Log("Welcome to Lumen Client");

		Debug.WriteLine(R"!(  _                                 )!");
		Debug.WriteLine(R"!( | |                                )!");
		Debug.WriteLine(R"!( | |    _   _ _ __ ___   ___ _ __   )!");
		Debug.WriteLine(R"!( | |   | | | | '_ ` _ \ / _ \ '_ \  )!");
		Debug.WriteLine(R"!( | |___| |_| | | | | | |  __/ | | | )!");
		Debug.WriteLine(R"!( |______\__,_|_| |_| |_|\___|_| |_| )!");
		Debug.WriteLine(R"!(                                    )!");
	}
}

#include <indxe>
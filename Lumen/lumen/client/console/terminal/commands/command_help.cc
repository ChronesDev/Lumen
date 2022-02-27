#pragma once

#include <lumen/log/log.cc>

#include <indxs>

namespace Lumen::Terminal::Commands
{
	global fun ExecuteHelp(string command, List<string> args)->void
	{
		using namespace rang;

		Log.NewLine();
		Log.Custom(fg::cyan, "help \t", fg::gray," - Displays this output");
		Log.NewLine();
	}
}

#include <indxe>
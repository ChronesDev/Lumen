#include "entry.cc"

#include <lumen/client/console/console_client.cc>
#include <lumen/helper/helper.cc>
#include <lumen/log/log.cc>

#include <indxs>

namespace Lumen
{
    fun Entry()->void
    {
        Helper::TryMakeConsole();
        Helper::EnableConsoleAnsiCodes();
        // Helper::ConfigureConsoleStyle();
        SetConsoleTitle("Lumen Client");

        rang::setWinTermMode(rang::winTerm::Ansi);

        Terminal::ConsoleEntry();

        Helper::DestroyConsole();
    }
}

#include <indxe>
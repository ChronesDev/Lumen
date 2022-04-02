#include "log.cc"

#include <indxs>

namespace Lumen
{
    fun Log_::TerminalInput()->string
    {
        using namespace rang;

        Console.Write(" ", fgB::cyan, "~ ", fgB::cyan);
        var ret = Console.ReadLine();
        Console.Write(fg::reset);
        return ret;
    }

    fun Log_::NewLine()->void { Console.WriteLine(); }

    fun Log_::DelLine()->void { Console.Write("\33[2K\r"); }

    fun Log_::GoToLastLine()->void
    {
        Console.Write("\x1b[0C");
        Console.Write("\x1b[1F");
    }

    fun Log_::Clear()->void
    {
        system("cls");
    }
}

#include <indxe>

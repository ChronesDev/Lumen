#include "log.cc"

#include <indxs>

namespace Lumen
{
    fun Log_::TerminalInput()->string
    {
        using namespace rang;

        Debug.Write(" ", fgB::cyan, "~ ", fgB::cyan);
        var ret = Console.ReadLine();
        Debug.Write(fg::reset);
        return ret;
    }

    fun Log_::NewLine()->void { Debug.WriteLine(); }

    fun Log_::DelLine()->void { Debug.Write("\33[2K\r"); }

    fun Log_::GoToLastLine()->void
    {
        Debug.Write("\x1b[0C");
        Debug.Write("\x1b[1F");
    }

    fun Log_::Clear()->void
    {
        system("cls");
    }
}

#include <indxe>

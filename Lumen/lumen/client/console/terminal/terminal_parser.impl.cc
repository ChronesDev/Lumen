#include "terminal_parser.cc"

#include <lumen/helper/helper.cc>
#include <lumen/log/log.cc>

#include "terminal_commands.cc"

#include <indxs>

static fun SplitCommand_(const string& s)->List<string>;

static fun TrimLeft_(string s)->string;
static fun TrimRight_(string s)->string;
static fun Trim_(string s)->string;

namespace Lumen::Terminal
{
    fun ProcessCommand(string input)->void
    {
        using namespace rang;

        var s1 = Trim_(input);
        var args = SplitCommand_(s1);

        if (args.Length == 0) return;

        var command = args.First;
        args.Erase(args.begin());

        var result = ExecuteCommand(command, args);
        if (!result)
        {
            Log.Fail("The command ", fg::black, bgB::red, command, fgB::red, bg::reset, " was not found.");
        }
    }
}

static fun SplitCommand_(const string& s)->List<string>
{
    List<string> ret;
    string s1 = "";
    for (int i = 0; i < s.Length; i++)
    {
        if (s[i] == ' ')
        {
            if (s1 != "")
            {
                ret.Add(s1);
                s1 = "";
            }
            continue;
        }

        s1 += s[i];
    }
    if (s1 != "") ret.Add(s1);

    return ret;
}

static fun TrimLeft_(string s)->string
{
    size_t start = s.find_first_not_of(' ');
    return (start == std::string::npos) ? "" : s.substr(start);
}
static fun TrimRight_(string s)->string
{
    size_t end = s.find_last_not_of(' ');
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}
static fun Trim_(string s)->string
{
    var s1 = TrimLeft_(s);
    var s2 = TrimRight_(s1);
    return s2;
}

#include <indxe>
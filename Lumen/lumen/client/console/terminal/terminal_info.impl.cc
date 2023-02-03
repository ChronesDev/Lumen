#include "terminal_info.cc"

#include <lumen/config/config.cc>
#include <lumen/client/console/console_client.cc>
#include <lumen/log/log.cc>

#include <indxs>

namespace Lumen::Terminal
{
    fun DisplayInfo()->void
    {
        using namespace rang;

        Log.NewLine();
        PrintTitle();

        Log.Custom("Platform: x64 | 64bit");

#if defined(INDEX_MSVC)
        Log.Custom("Compiler: MSVC");
#elif defined(INDEX_Clang)
        Log.Custom("Compiler: Clang");
#else
        Log.Custom("Compiler: Other");
#endif

        Log.Custom("Client Version: ", (string)Config::ClientVersion);

        Log.Custom("Target Version: ", (string)Config::TargetVersion);
        Log.Custom("Target Package Version: ", (string)Config::TargetPackageVersion);
        Log.NewLine();
    }
}

#include <indxe>
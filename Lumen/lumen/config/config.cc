#pragma once

#include <indx>

#include <indxs>

namespace Lumen::Config
{
    global var ClientVersion =
        Version {0, 1};
        //::Parse("0.1");

    global var TargetVersion =
        Version {1, 18, 12};
        //Version::Parse("1.18.12");
    global var TargetPackageVersion =
        Version {1, 18, 1201, 0};
        //Version::Parse("1.18.1201.0");
}

#include <indxe>
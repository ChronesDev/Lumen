#pragma once

#include <indx>

#include <indxs>

namespace Lumen::Signature
{
    global string KeyboardEvent = "48 89 5C 24 ?? 57 48 83 EC ?? 8B 05 ?? ?? ?? ?? 8B DA 89 54 24 ??";

    global string MouseEvent = "48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 57 41 54 41 55 41 56 41 57 48 83 "
                               "EC 60 44 0F B7 BC 24 B0 00 00 00 48 8B D9 44 0F B7 A4 24 B8 00 00 00 33 F6 44 "
                               "0F B7 AC 24 C0 00 00 00";

    global string GetFov = "40 53 48 83 EC 70 0F 29 7C 24 50 44 0F 29 44 24 40 48 8B";

    global string GetGamma = "48 83 EC 28 80 B9 81 12 00 00 00 48 8D 54 24 30 48 8B 01 74 35 41 B8 15";

    global string GetWorldTime = "48 8B 81 50 02 00 00 48 85 C0 74 07 8B 80 50";
}

#include <indxe>
#pragma once

#include <indx>

#include <indxs>

namespace Lumen::Signature
{
    // Safe: 48 83 EC 48 0F B6 C1 4C 8D 05 ?? ?? ?? ?? 89 54 24 ?? 88 4C 24 ?? 41 89 14 80 8B 05 ?? ?? ?? ?? 48 8B 15
    // Short: 48 83 EC 48 0F B6 C1 4C 8D
    global string KeyboardEvent = "48 83 EC 48 0F B6 C1 4C 8D";

    global string MouseEvent = "48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 57 41 54 41 55 41 56 41 57 48 83 "
                               "EC 60 44 0F B7 BC 24 B0 00 00 00 48 8B D9 44 0F B7 A4 24 B8 00 00 00 33 F6 44 "
                               "0F B7 AC 24 C0 00 00 00";

    global string GetFov = "40 53 48 83 EC 70 0F 29 7C 24 50 44 0F 29 44 24 40 48 8B";

    global string GetGamma = "48 83 EC 28 80 B9 B9 12 00 00 00 48 8D 54 24 30 48 8B 01 74 35 41 B8 16";

    global string GetWorldTime = "48 8B 81 50 02 00 00 48 85 C0 74 07 8B 80 50";

    // TODO: Remove that
    /*? 1.18.12
     ** Minecraft.Windows.exe+1713CC7 - F3 0F10 40 14         - movss xmm0,[rax+14]
     ** begins at: Minecraft.Windows.exe+1713C30 - 4C 8B D1              - mov r10,rcx
     */
    global string GetMouseSensitivity = "4C 8B D1 44 0F B6 CA 49 BB B3 01 00 00 00 01 00 00 48 B8 25 23 22 84 "
                                        "E4 9C F2 CB 4C 33 C8 8B C2 4D 0F AF CB C1 E8 08 44 0F B6 C0 8B C2 4D "
                                        "33 C8 C1 E8 10 4D 8B 42 30 4D 0F AF CB 0F B6 C8 4C 33 C9 8B C2 49 8B "
                                        "4A 48";
}

#include <indxe>
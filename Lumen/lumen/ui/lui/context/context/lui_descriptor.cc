#pragma once

#include <indx-ui>

#include <lumen/input/key.cc>
#include <lumen/input/key_state.cc>

#include <indxs>

namespace Lumen::LUI
{
    struct LUIInputDescriptor : UIInputDescriptor
    {
        using TKey = Lumen::Key;
        using TKeyState = Lumen::KeyState;
    };
}

#include <indxe>
#pragma once

#include <indx-ui>

#include <lumen/input/key.cc>

#include <indxs>

namespace Lumen::LUI
{
    struct LUIInputDescriptor : UIInputDescriptor
    {
        using TKey = Lumen::Key;
    };
}

#include <indxe>
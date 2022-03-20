#include "data.cc"

#include <indxs>

fun Lumen_Data_LoadDataDir_()->void;

namespace Lumen::Data
{
    bool Initialized_ = false;

    fun Init()->void
    {
        if (Initialized_) INDEX_THROW("Already initialized.");

        Lumen_Data_LoadDataDir_();
    }

    fun Deinit()->void
    {
        if (!Initialized_) INDEX_THROW("Already deinitialized.");
    }
}

#include <indxe>
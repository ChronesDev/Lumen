#pragma once

#include <filesystem>
#include <ryml/ryml.hpp>

#include <indx>

#include <indxs>

namespace Lumen::Data
{
    global std::filesystem::path DataPath = "";
    global string DataDirectory = "";

    fun Init()->void;
    fun Deinit()->void;
}

#include <indxe>
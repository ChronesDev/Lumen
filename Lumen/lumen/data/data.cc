#pragma once

#include <filesystem>
#include <ryml/ryml.hpp>

#include <indx>

#include <indxs>

namespace Lumen::Data
{
    global std::filesystem::path DataPath = "";
    global string DataDirectory = "";

    global std::filesystem::path MinecraftDataPath = "";
    global string MinecraftDataDirectory = "";

    fun Init()->void;
    fun Deinit()->void;
}

#include <indxe>
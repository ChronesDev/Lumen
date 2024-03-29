#pragma once

#include <filesystem>
#include <nlohmann/json.hpp>

#include <indx>

#include <indxs>

namespace Lumen::Data
{
    global std::filesystem::path DataPath = "";
    global string DataDirectory = "";

    global std::filesystem::path ConfigPath = "";
    global string ConfigDirectory = "";

    global std::filesystem::path MinecraftDataPath = "";
    global string MinecraftDataDirectory = "";

    fun Init()->void;
    fun Deinit()->void;

    fun IsConfigNameValid(string name)->bool;
    fun IsConfigValid(nlohmann::json& j)->bool;
    fun CheckConfig(nlohmann::json& j)->void;
    fun MakeConfigData(string name)->nlohmann::json;
    fun LoadConfigData(nlohmann::json& j)->void;
}

#include <indxe>
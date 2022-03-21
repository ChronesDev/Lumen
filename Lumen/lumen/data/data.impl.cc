#include "data.cc"

#include <lumen/config/config.cc>

#include <indxs>

fun Lumen_Data_LoadDataDir_()->void;

namespace Lumen::Data
{
    bool Initialized_ = false;

    fun Init()->void
    {
        if (Initialized_) INDEX_THROW("Already initialized.");

        Lumen_Data_LoadDataDir_();

        if (!std::filesystem::exists(DataPath)) std::filesystem::create_directories(DataPath);

        ConfigPath
            = DataPath / "ver" / (std::string)Str("v", Config::ClientVersion.Major, ".", Config::ClientVersion.Minor);
        ConfigDirectory = ConfigPath.string();
        if (!std::filesystem::exists(ConfigPath)) std::filesystem::create_directories(ConfigPath);
    }

    fun Deinit()->void
    {
        if (!Initialized_) INDEX_THROW("Already deinitialized.");
    }
}

#include <indxe>
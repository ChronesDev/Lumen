#include "data.cc"

#include <winrt/windows.storage.h>

#include <indxs>

fun Lumen_Data_LoadDataDir_()->void
{
    using namespace winrt;

    // Minecraft Data Directory
    {
        var localFolder = winrt::Windows::Storage::ApplicationData::Current().LocalFolder();
        var localFolderPath = localFolder.Path();
        std::wstring dataDirectory = localFolderPath.c_str();

        var dataDirectoryUnixStyle = dataDirectory;
        for (var& c : dataDirectoryUnixStyle)
        {
            if (c == L'\\') { c = L'/'; }
        }

        Lumen::Data::MinecraftDataPath = std::filesystem::path(dataDirectoryUnixStyle);

        var d = dataDirectory;
        var s = string();
        std::transform(d.begin(), d.end(), std::back_inserter(s), [](wchar_t c) { return (char)c; });

        Lumen::Data::MinecraftDataDirectory = Lumen::Data::MinecraftDataPath.string();

        //Debug.Log("MinecraftDataDirectory: ", Lumen::Data::MinecraftDataDirectory);
    }

    // Data Directory
    {
        Lumen::Data::DataPath = Lumen::Data::MinecraftDataPath / "client" / "lumen";
        Lumen::Data::DataDirectory =  Lumen::Data::DataPath.string();

        Debug.Log("DataDirectory: ", Lumen::Data::DataDirectory);
    }
}

#include <indxe>
#include "data.cc"

#include <winrt/windows.storage.h>

#include <indxs>

/**
 * Yoinked from Horion (sorry). Source: https://github.com/horionclient/Horion/blob/master/Utils/Logger.cpp
 */
fun Lumen_Data_LoadDataDir_()->void
{
    using namespace winrt;

    var localFolder = winrt::Windows::Storage::ApplicationData::Current().AC();
    var localFolderPath = localFolder.Path();
    std::wstring dataDirectory = localFolderPath.c_str();

    var dataDirectoryUnixStyle = dataDirectory;
    for (var& c : dataDirectoryUnixStyle)
    {
        if (c == L'\\') { c = L'/'; }
    }

    Lumen::Data::DataPath = std::filesystem::path(dataDirectoryUnixStyle);

    var d = dataDirectory;
    var s = string();
    std::transform(d.begin(), d.end(), std::back_inserter(s), [](wchar_t c) { return (char)c; });

    Lumen::Data::DataDirectory = Lumen::Data::DataPath.string();

    Debug.Log("DataDirectory: ", Lumen::Data::DataPath.string());
}

#include <indxe>
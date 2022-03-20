#include "data.cc"

#include <windows.storage.h>
#include <wrl.h>

#include <indxs>

using namespace ABI::Windows::Storage;
using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;

/**
 * Yoinked from Horion (sorry). Source: https://github.com/horionclient/Horion/blob/master/Utils/Logger.cpp
 */
fun Lumen_Data_LoadDataDir_()->void
{
    ComPtr<IApplicationDataStatics> appDataStatics;
    auto hr = RoGetActivationFactory(
        HStringReference(L"Windows.Storage.ApplicationData").Get(), __uuidof(appDataStatics), &appDataStatics);
    if (FAILED(hr)) INDEX_THROW("RoGetActivationFactory failed.");

    ComPtr<IApplicationData> appData;
    hr = appDataStatics->get_Current(&appData);
    if (FAILED(hr)) INDEX_THROW("appDataStatics->get_Current failed.");

    ComPtr<IStorageFolder> roamingFolder;
    hr = appData->get_RoamingFolder(&roamingFolder);
    if (FAILED(hr)) INDEX_THROW("Failed to retrieve roaming folder");

    ComPtr<IStorageItem> folderItem;
    hr = roamingFolder.As(&folderItem);
    if (FAILED(hr)) INDEX_THROW("Failed to cast roaming folder to IStorageItem");

    HString roamingPathHString;
    hr = folderItem->get_Path(roamingPathHString.GetAddressOf());
    if (FAILED(hr)) INDEX_THROW("Failed to retrieve roaming folder path");

    uint32_t pathLength;
    auto roamingPathCStr = roamingPathHString.GetRawBuffer(&pathLength);

    var dataDirectory = std::wstring(roamingPathCStr, pathLength);

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

    // Debug.Log("DataDirectory: ", Lumen::Data::DataPath.string());
}

#include <indxe>
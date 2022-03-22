#include "helper.cc"

#include <winrt/windows.applicationmodel.datatransfer.h>
#include <winrt/windows.foundation.h>

#include <indxs>

namespace Lumen::Helper
{
    fun SetClipboard(string text)->void
    {
        using namespace winrt::Windows::ApplicationModel::DataTransfer;

        var data = DataPackage();
        data.SetText(winrt::to_hstring(text));
        Clipboard::SetContent(data);
        Clipboard::Flush();
    }

    fun GetClipboard()->string
    {
        using namespace winrt::Windows::ApplicationModel::DataTransfer;

        var content = Clipboard::GetContent();
        var textAsync = content.GetTextAsync();
        var text = textAsync.get();

        return winrt::to_string(text);
    }
}

#include <indxe>
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

//        int size = ::MultiByteToWideChar(CP_UTF8, 0, text.CStr, -1, nullptr, 0);
//        if (size < 0) { return; }
//
//        if (::OpenClipboard(nullptr))
//        {
//            ::EmptyClipboard();
//            HGLOBAL hGlobal = ::GlobalAlloc(GMEM_ZEROINIT | GMEM_MOVEABLE | GMEM_DDESHARE, (size + 1) * sizeof(WCHAR));
//            if (hGlobal != nullptr)
//            {
//                auto lpszData = (LPWSTR)::GlobalLock(hGlobal);
//                if (lpszData != nullptr)
//                {
//                    ::MultiByteToWideChar(CP_UTF8, 0, text.CStr, -1, lpszData, size);
//                    ::GlobalUnlock(hGlobal);
//                    ::SetClipboardData(CF_UNICODETEXT, hGlobal);
//                }
//            }
//            ::CloseClipboard();
//        }
//        else
//            INDEX_THROW("Failed");
    }

    fun GetClipboard()->string
    {
// using namespace winrt::Windows::ApplicationModel::DataTransfer;
//
// var content = Clipboard::GetContent();
// var textAsync = content.GetTextAsync();
// var text = textAsync.get();
//
// return winrt::to_string(text);

        std::string ret;
        if (::OpenClipboard(nullptr))
        {
            HGLOBAL hGlobal = ::GetClipboardData(CF_UNICODETEXT);
            if (hGlobal != nullptr)
            {
                auto lpszData = (LPWSTR)::GlobalLock(hGlobal);
                if (lpszData != nullptr)
                {
                    int size = ::WideCharToMultiByte(CP_UTF8, 0, lpszData, -1, nullptr, 0, nullptr, nullptr);
                    if (size > 0)
                    {
                        ret.resize(size + 1);
                        ::WideCharToMultiByte(CP_UTF8, 0, lpszData, -1, &ret[0], size, nullptr, nullptr);
                    }
                    ::GlobalUnlock(hGlobal);
                }
            }
            ::CloseClipboard();
        }
        else
            INDEX_THROW("Failed");
        return ret;
    }
}

#include <indxe>
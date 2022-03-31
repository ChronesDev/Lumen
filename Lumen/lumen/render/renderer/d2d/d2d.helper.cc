#pragma once

#include <winrt/base.h>

#include <indx>

#include <indxs>

namespace Lumen::Render::D2D
{
    using winrt::com_ptr;

    class ComException : public std::exception
    {
    public:
        explicit ComException(HRESULT hr)
            : result(hr)
        {
        }

        [[nodiscard]] fun what() const->const char* override
        {
            static char s_str[64] = {};
            sprintf_s(s_str, "Failure with HRESULT of %08X", static_cast<unsigned int>(result));
            return s_str;
        }

    private:
        HRESULT result;
    };

    global fun ThrowIfFailed(HRESULT hr)
    {
        if (FAILED(hr)) { throw ComException(hr); }
    }

    template <class T> global fun MakeSizedList(size_t length, T defaultValue = {})->List<T>
    {
        List<T> list;
        for (int k = 0; k < length; ++k)
        {
            list.push_back(defaultValue);
        }
        return list;
    }
}

#include <indxe>
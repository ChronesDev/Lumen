#pragma once

#include <winrt/base.h>
#include <lumen/ext/d2d/d2d.cc>

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

namespace Lumen::Render::D2D
{
    global fun CopyBitmap(ID2D1DeviceContext* dc, com_ptr<ID2D1Bitmap>& from, com_ptr<ID2D1Bitmap>& to)
    {
        if (from.get() == nullptr) throw std::exception("from was nullptr.");

        if (to.get() == nullptr)
        {
            D2D1_BITMAP_PROPERTIES props = D2D1::BitmapProperties(from->GetPixelFormat());
            ThrowIfFailed(dc->CreateBitmap(from->GetPixelSize(), props, to.put()));
        }
        else if (from->GetPixelSize() != to->GetPixelSize())
        {
            to = nullptr;
            D2D1_BITMAP_PROPERTIES props = D2D1::BitmapProperties(from->GetPixelFormat());
            ThrowIfFailed(dc->CreateBitmap(from->GetPixelSize(), props, to.put()));
        }

        var destPoint = D2D1::Point2U(0, 0);
        var size = from->GetPixelSize();
        var rect = D2D1::RectU(0, 0, size.width, size.height);
        to->CopyFromBitmap(&destPoint, from.get(), &rect);
    }
    global fun CopyBitmap(ID2D1DeviceContext* dc, com_ptr<ID2D1Bitmap1>& from, com_ptr<ID2D1Bitmap>& to)
    {
        if (from.get() == nullptr) throw std::exception("from was nullptr.");

        if (to.get() == nullptr)
        {
            D2D1_BITMAP_PROPERTIES props = D2D1::BitmapProperties(from->GetPixelFormat());
            ThrowIfFailed(dc->CreateBitmap(from->GetPixelSize(), props, to.put()));
        }
        else if (from->GetPixelSize() != to->GetPixelSize())
        {
            to = nullptr;
            D2D1_BITMAP_PROPERTIES props = D2D1::BitmapProperties(from->GetPixelFormat());
            ThrowIfFailed(dc->CreateBitmap(from->GetPixelSize(), props, to.put()));
        }

        var destPoint = D2D1::Point2U(0, 0);
        var size = from->GetPixelSize();
        var rect = D2D1::RectU(0, 0, size.width, size.height);
        to->CopyFromBitmap(&destPoint, from.get(), &rect);
    }
}

#include <indxe>
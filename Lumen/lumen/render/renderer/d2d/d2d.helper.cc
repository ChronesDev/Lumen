#pragma once

#include <lumen/ext/d2d/d2d.cc>
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
    global fun CopyBitmap(ID2D1DeviceContext* dc, com_ptr<ID2D1Bitmap1>& from, com_ptr<ID2D1Bitmap1>& to)
    {
        if (from.get() == nullptr) throw std::exception("from was nullptr.");

        if (to.get() == nullptr)
        {
            D2D1_BITMAP_PROPERTIES1 props = D2D1::BitmapProperties1();
            props.pixelFormat = from->GetPixelFormat();
            ThrowIfFailed(dc->CreateBitmap(from->GetPixelSize(), nullptr, 0, props, to.put()));
        }
        else if (from->GetPixelSize() != to->GetPixelSize())
        {
            to = nullptr;
            D2D1_BITMAP_PROPERTIES1 props = D2D1::BitmapProperties1();
            props.pixelFormat = from->GetPixelFormat();
            ThrowIfFailed(dc->CreateBitmap(from->GetPixelSize(), nullptr, 0, props, to.put()));
        }

        var destPoint = D2D1::Point2U(0, 0);
        var size = from->GetPixelSize();
        var rect = D2D1::RectU(0, 0, size.width, size.height);
        to->CopyFromBitmap(&destPoint, from.get(), &rect);
    }

    global fun CreateBitmapIfNeeded(ID2D1DeviceContext* dc, com_ptr<ID2D1Bitmap>& bitmap, D2D1_SIZE_U size,
        const D2D1_BITMAP_PROPERTIES& properties)
    {
        if (bitmap == nullptr) dc->CreateBitmap(size, properties, bitmap.put());
        elif (bitmap->GetPixelSize() != size)
        {
            bitmap = nullptr;
            dc->CreateBitmap(size, properties, bitmap.put());
        }
    }
    global fun CreateBitmapIfNeeded(ID2D1DeviceContext* dc, com_ptr<ID2D1Bitmap1>& bitmap, D2D1_SIZE_U size,
        const D2D1_BITMAP_PROPERTIES1& properties)
    {
        if (bitmap == nullptr) dc->CreateBitmap(size, nullptr, 0, properties, bitmap.put());
        elif (bitmap->GetPixelSize() != size)
        {
            bitmap = nullptr;
            dc->CreateBitmap(size, nullptr, 0, properties, bitmap.put());
        }
    }

    struct MakeBlurBufferArgs
    {
        com_ptr<ID2D1Bitmap1>& BackBuffer;
        com_ptr<ID2D1Image>& BlurBuffer;
        Nullable<com_ptr<ID2D1Effect>*> BlurEffect;
        float Sigma = 10.0f;
    };

    global fun MakeBlurBuffer(ID2D1DeviceContext* dc, MakeBlurBufferArgs args)->void
    {
        var& backBuffer = args.BackBuffer;
        var& blurBuffer = args.BlurBuffer;
        var& blurEffect = args.BlurEffect;
        var sigma = args.Sigma;

        if (backBuffer.get() == nullptr) throw std::exception("backBuffer was nullptr.");

        if (!blurEffect.HasValue) blurEffect = nullptr;

        if (blurEffect.Value->get() == nullptr)
        {
            ThrowIfFailed(dc->CreateEffect(CLSID_D2D1GaussianBlur, blurEffect.Value->put()));
        }

        var blur = blurEffect.Value->get();
        blur->SetInput(0, backBuffer.get());
        blur->SetValue(D2D1_GAUSSIANBLUR_PROP_STANDARD_DEVIATION, sigma);
        blur->SetValue(D2D1_GAUSSIANBLUR_PROP_BORDER_MODE, D2D1_BORDER_MODE_HARD);
        blur->SetValue(D2D1_GAUSSIANBLUR_PROP_OPTIMIZATION, D2D1_GAUSSIANBLUR_OPTIMIZATION_QUALITY);

        blurBuffer = nullptr;
        blur->GetOutput(blurBuffer.put());
    }
}

#include <indxe>
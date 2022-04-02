#pragma once

#include "lui_element.cc"

#include <indxs>

namespace Lumen::LUI
{
    struct LUIRenderElement : virtual LUIElement
    {
    protected:
        void OnRender() override
        {
            if (!lc) return;
            if (LUIDrawable* d = lc->dw; d) OnLRender(d);
        }

    public:
        void OnPostRender() override
        {
            if (!lc) return;
            if (LUIDrawable* d = lc->dw; d) OnLPostRender(d);
        }

    protected:
        virtual void OnLRender(LUIDrawable* d) {};
        virtual void OnLPostRender(LUIDrawable* d) {};
    };
}

#include <indxe>
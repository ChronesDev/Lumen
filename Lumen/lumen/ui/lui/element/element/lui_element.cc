#pragma once

#include <lumen/ui/lui/context/context/lui_context.cc>

#include <indxs>

namespace Lumen::LUI
{
    struct LUIElement : virtual UIElement
    {
    protected:
        union
        {
            LUIContext* LContext_ = nullptr;
            LUIContext* lc;
        };

    protected:
        void LUIElement_OnAttachedToUIRoot_(IPtr<IUIRoot> root)
        {
            Log("LUIElement_OnAttachedToUIRoot_ Attached.");
            auto ptr = dynamic_cast<LUIContext*>(root.Ptr);
            if (ptr)
            {
                LContext_ = ptr;
                LContext_Register_(ptr);
                UpdateResources();
            }
        }
        void LUIElement_OnDetachedFromUIRoot_()
        {
            Log("LUIElement_OnAttachedToUIRoot_ Detached.");
            if (LContext_) { LContext_Unregister_(LContext_); }
            LContext_ = nullptr;

            ReleaseResources();
        }

        void OnAttachedToUIRoot_(IPtr<IUIRoot> root) override
        {
            LUIElement_OnAttachedToUIRoot_(root);
            UIElement::OnAttachedToUIRoot_(root);
        }
        void OnDetachedFromUIRoot_() override
        {
            LUIElement_OnDetachedFromUIRoot_();
            UIElement::OnDetachedFromUIRoot_();
        }

    protected:
        void LContext_Register_(LUIContext* r)
        {
            r->AddResourcesUpdateCallback(ISelf(), [this] { OnResourcesUpdate(); });
            r->AddResourcesReleaseCallback(ISelf(), [this] { OnResourcesRelease(); });
        }
        void LContext_Unregister_(LUIContext* r)
        {
            r->RemoveResourcesUpdateCallback(ISelf());
            r->RemoveResourcesReleaseCallback(ISelf());
        }

    public:
        virtual void UpdateResources() { OnResourcesUpdate(); }
        virtual void ReleaseResources() { OnResourcesRelease(); }

    protected:
        virtual void OnResourcesUpdate() = 0;
        virtual void OnResourcesRelease() = 0;
    };
}

#include <indxe>
#pragma once

#include <lumen/ui/lui/common/common.cc>

#include "lui_descriptor.cc"

#include <indxs>

namespace Lumen::LUI
{
    struct LUIContext : virtual UIInputContext<LUIInputDescriptor>
    {
    protected:
        winrt::com_ptr<LUIDrawable> DrawContext_;

    public:
        fun SetDrawContext(const winrt::com_ptr<LUIDrawable>& value)
        {
            if (DrawContext_ != value)
            {
                DrawContext_ = value;
                if (value.get()) TriggerResourcesUpdate();
                else TriggerResourcesRelease();
            }
        }

    public:
        fun GetDrawContext() const->LUIDrawable* { return DrawContext_.get(); }
        INDEX_Property(get = GetDrawContext) LUIDrawable* dw;

    public:
        fun TriggerResourcesUpdate()->void
        {
            for (var& v : ResourcesUpdate)
            {
                if (!v.first) continue;
                if (!v.second) continue;
                v.second();
            }
        }
        fun TriggerResourcesRelease()->void
        {
            for (var& v : ResourcesRelease)
            {
                if (!v.first) continue;
                if (!v.second) continue;
                v.second();
            }
        }

    public:
        std::list<std::pair<IPtr<UIElement>, std::function<void()>>> ResourcesUpdate;

        fun AddResourcesUpdateCallback(const IPtr<UIElement>& e, const std::function<void()>& f)->void
        {
            ResourcesUpdate.emplace_back(e, f);
        }
        fun RemoveResourcesUpdateCallback(const IPtr<UIElement>& e)->void
        {
            var p = e.Ptr;
            ResourcesUpdate.remove_if([p](const auto& it) { return it.first.Ptr == p; });
        }

    public:
        std::list<std::pair<IPtr<UIElement>, std::function<void()>>> ResourcesRelease;

        fun AddResourcesReleaseCallback(const IPtr<UIElement>& e, const std::function<void()>& f)->void
        {
            ResourcesRelease.emplace_back(e, f);
        }
        fun RemoveResourcesReleaseCallback(const IPtr<UIElement>& e)->void
        {
            var p = e.Ptr;
            ResourcesRelease.remove_if([p](const auto& it) { return it.first.Ptr == p; });
        }
    };
}

#include <indxe>
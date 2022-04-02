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
        fun GetDrawContext() const->LUIDrawable* { return DrawContext_.get(); }
        INDEX_Property(get = GetDrawContext) LUIDrawable* dw;

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
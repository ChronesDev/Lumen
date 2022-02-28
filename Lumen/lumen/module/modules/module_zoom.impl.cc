#include "module_zoom.cc"

#include <indxs>

namespace Lumen::Modules
{
    fun Zoom::OnInit()->void
    {
        if (!ZoomModule.IsNull) INDEX_THROW("Duplicate of " + Name + " found.");
        ZoomModule = ISelf().DynamicAs<Zoom>();
    }

    fun Zoom::OnDeinit()->void
    {
        var self = ISelf();
        ZoomModule = nullptr;
    }
}

#include <indxe>
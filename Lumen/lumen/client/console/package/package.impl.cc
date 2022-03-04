#include "package.cc"

#include <winrt/Windows.ApplicationModel.Core.h>

#include <indxs>

namespace Lumen::Package
{
    fun PackageVersion()->Version
    {
        using namespace winrt;

        var package = Windows::ApplicationModel::Package::Current();
        var packageId = package.Id();
        var packageVersion = packageId.Version();
        return {
            (short)packageVersion.Major, (short)packageVersion.Minor, (short)packageVersion.Build,
            (short)packageVersion.Revision };
    }
}

#include <indxe>
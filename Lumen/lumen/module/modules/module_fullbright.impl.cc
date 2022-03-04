#include "module_fullbright.cc"

#include <lumen/detour/detour.cc>
#include <lumen/input/input.cc>
#include <lumen/log/log.cc>
#include <lumen/signature/signature.cc>

#include <indxs>

static fun OnGetGamma_(void* that)->float;
static fun OnKeyEvent_(Lumen::Key key, Lumen::KeyState state, bool& handled, bool& cancel)->void;

namespace Lumen::Modules
{
    fun Fullbright::OnInit()->void
    {
        if (!FullbrightModule.IsNull) INDEX_THROW("Duplicate of " + Name + " found.");
        FullbrightModule = ISelf().DynamicAs<Fullbright>();

        var result = Mem.FindSignature(Signature::GetGamma);
        Detour::GetGammaDetour.Hook(result, Detour::GetGammaOriginal, OnGetGamma_);
        Log("(Fullbright) Hooked GetGammaDetour");
    }

    fun Fullbright::OnDeinit()->void
    {
        var self = ISelf();
        FullbrightModule = nullptr;
    }
}

static fun OnGetGamma_(void* that)->float
{
    using namespace Lumen;
    using namespace Lumen::Modules;

    if (FullbrightModule.IsNull) INDEX_THROW("FullbrightModule was null.");

    var gamma = Detour::GetGammaOriginal(that);
    if (FullbrightModule->IsDisabled) return gamma;

    return 15.f;
}

#include <indxe>
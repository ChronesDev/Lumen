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

        Input::KeyEvent += OnKeyEvent_;
        Log("(Fullbright) Registered to KeyEvent");

        var result = Mem.FindSignature(Signature::GetGamma);
        Detour::GetGammaDetour.Hook(result, Detour::GetGammaOriginal, OnGetGamma_);
        Log("(Fullbright) Hooked GetFovDetour");
    }

    fun Fullbright::OnDeinit()->void
    {
        var self = ISelf();
        FullbrightModule = nullptr;

        Input::KeyEvent -= OnKeyEvent_;
        Log("(Fullbright) Unregistered from KeyEvent");
    }
}

static fun OnGetGamma_(void* that)->float
{
    using namespace Lumen;
    using namespace Lumen::Modules;

    if (FullbrightModule.IsNull) INDEX_THROW("FullbrightModule was null.");
    if (FullbrightModule->IsDisabled) return Detour::GetGammaOriginal(that);

    return 15.f;
}

static fun OnKeyEvent_(Lumen::Key key, Lumen::KeyState state, bool& handled, bool& cancel)->void
{
    using namespace Lumen;
    using namespace Lumen::Modules;

    if (FullbrightModule.IsNull) INDEX_THROW("FullbrightModule was null.");

    if (FullbrightModule->IsDisabled) FullbrightModule->Enable();
    else FullbrightModule->Disable();
}

#include <indxe>
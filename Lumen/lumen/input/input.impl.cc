#include "input.cc"

#include <lumen/detour/detour.cc>
#include <lumen/signature/signature.cc>

#include <indxs>

static fun OnKeyEvent_(ulong id, ulong value)->void;

namespace Lumen::Input
{
	static bool Initialized_ = false;

	fun Init()->void
	{
		if (Initialized_) return;
		Initialized_ = true;

		// TODO: Get KeyboardEvent Address
		var result = Mem.FindSignature(Signature::KeyboardEvent);
		Detour::KeyboardEventDetour.Hook(result, Detour::KeyboardEventOriginal, OnKeyEvent_);
	}

	fun Deinit()->void
	{
		if (!Initialized_) return;
		Initialized_ = false;

		Detour::KeyboardEventDetour.UnhookIfEnabled();
	}
}

static fun OnKeyEvent_(ulong id, ulong value)->void
{

}

#include <indxe>
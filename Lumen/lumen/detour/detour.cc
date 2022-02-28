#pragma once

#include <indx>

#include "simple_detour.cc"

#include <indxs>

namespace Lumen::Detour
{
	typedef void (*KeyboardEventFunc)(ulong id, ulong value);
	global KeyboardEventFunc KeyboardEventOriginal = { };
	global SimpleDetour KeyboardEventDetour;

	typedef void (*MouseEventFunc)(
		UInt64 arg1, UInt64 arg2, UInt64 arg3, UInt64 arg4, UInt64 arg5, UInt64 arg6, UInt64 arg7
	);
	global MouseEventFunc MouseEventOriginal = { };
	global SimpleDetour MouseEventDetour;
}

#include <indxe>
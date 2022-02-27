#include "helper.cc"

#include <Windows.h>

#include <indxs>

namespace Lumen::Helper
{
	fun TryMakeConsole() -> void
	{
#ifdef INDEX_DEBUG
		MakeConsole();
#endif
	}

	fun MakeConsole() -> void
	{
		if (!::AllocConsole()) INDEX_THROW("AllocConsole returned false.");

		FILE* dummy;
		freopen_s(&dummy, "CONIN$", "r", stdin);
		freopen_s(&dummy, "CONOUT$", "w", stderr);
		freopen_s(&dummy, "CONOUT$", "w", stdout);
	}
}

#include <indxe>
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

		FILE *dummy;
		freopen_s(&dummy, "CONIN$", "r", stdin);
		freopen_s(&dummy, "CONOUT$", "w", stderr);
		freopen_s(&dummy, "CONOUT$", "w", stdout);
	}

	fun EnableConsoleAnsiCodes() -> void
	{
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		if (hOut == INVALID_HANDLE_VALUE) INDEX_THROW("GetStdHandle failed.");

		DWORD dwMode = 0;
		if (!GetConsoleMode(hOut, &dwMode)) INDEX_THROW("GetConsoleMode failed.");

		dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
		if (!SetConsoleMode(hOut, dwMode)) INDEX_THROW("SetConsoleMode failed.");
	}
}

#include <indxe>
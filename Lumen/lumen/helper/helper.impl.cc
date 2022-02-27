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

	fun ConfigureConsoleStyle()->void
	{
		static Vec2S consoleSize { 98, 24 };

		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		if (hOut == INVALID_HANDLE_VALUE) INDEX_THROW("GetStdHandle failed.");

		SMALL_RECT DisplayArea = {0, 0, 0, 0};
		int x = consoleSize.X;
		int y = consoleSize.Y;

		DisplayArea.Right  = x;
		DisplayArea.Bottom = y;

		SetConsoleWindowInfo(hOut, TRUE, &DisplayArea);

		CONSOLE_FONT_INFOEX cfi;
		cfi.cbSize = sizeof(cfi);
		cfi.nFont = 0;
		cfi.dwFontSize.X = 0;                   // Width of each character in the font
		cfi.dwFontSize.Y = 20;                  // Height
		cfi.FontFamily = FF_DONTCARE;
		cfi.FontWeight = FW_MEDIUM;
		std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
		SetCurrentConsoleFontEx(hOut, FALSE, &cfi);
	}
}

#include <indxe>
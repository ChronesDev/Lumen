#pragma once

#include <indx>
#include <rang>

#include <indxs>

namespace Lumen
{
	struct Log_
	{
		template<class TArg, class... TArgs>
		fun operator()(TArg &&arg, TArgs &&... args) -> void
		{
			using namespace rang;

			Debug.Write(
				fg::magenta, " [Lumen] ", fg::reset, ": ", fg::gray, std::forward<TArg>(arg),
				std::forward<TArgs>(args)..., fg::reset
			);
		}

		template<class TArg, class... TArgs>
		fun Success(TArg &&arg, TArgs &&... args) -> void
		{
			using namespace rang;
			Debug.Log(" ", fgB::green, std::forward<TArg>(arg), std::forward<TArgs>(args)..., fg::reset);
		}

		template<class TArg, class... TArgs>
		fun Fail(TArg &&arg, TArgs &&... args) -> void
		{
			using namespace rang;
			Debug.Log(" ", fgB::red, std::forward<TArg>(arg), std::forward<TArgs>(args)..., fg::reset);
		}

		template<class TArg, class... TArgs>
		fun Custom(TArg &&arg, TArgs &&... args) -> void
		{
			using namespace rang;
			Debug.Log(" ", fgB::yellow, std::forward<TArg>(arg), std::forward<TArgs>(args)..., fg::reset);
		}

		fun TerminalInput()->string;

		fun NewLine()->void;
		fun DelLine() -> void;
	};

	global Log_ Log { };
}

#include <indxe>
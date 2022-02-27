#pragma once

#include <indx>
#include <rang>

#include <indxs>

namespace Lumen
{
	struct Log_
	{
		template<class TArg, class... TArgs>
		fun operator()(TArg && arg, TArgs &&... args) -> void
		{
			using namespace rang;

			Debug.Write(fg::magenta, " [Lumen] ", fg::reset, ": ", fg::gray, std::forward<TArg>(arg), std::forward<TArgs>(args)..., fg::reset);
		}
	};

	global Log_ Log { };
}

#include <indxe>
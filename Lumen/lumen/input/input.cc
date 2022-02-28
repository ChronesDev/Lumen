#pragma once

#include <indx>

#include "key.cc"
#include "key_state.cc"
#include "key_helper.cc"

#include <indxs>

namespace Lumen::Input
{
	fun Init()->void;
	fun Deinit()->void;

	// OnKeyEvent(Key key, KeyState state, bool& handled, bool& cancel)->void
	global Event<void(Key key, KeyState state, bool& handled, bool& cancel)> KeyEvent;

	// OnKeyPressed(Key key, bool& handled, bool& cancel)->void
	global Event<void(Key key, bool& handled, bool& cancel)> KeyPressed;

	// OnKeyReleased(Key key, bool& handled, bool& cancel)->void
	global Event<void(Key key, bool& handled, bool& cancel)> KeyReleased;
}

#include <indxe>
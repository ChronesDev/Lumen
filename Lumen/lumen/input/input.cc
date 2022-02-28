#pragma once

#include <indx>

#include "key.cc"

#include <indxs>

namespace Lumen::Input
{
	fun Init()->void;
	fun Deinit()->void;

	// OnKeyEvent(Key key, bool pressed, bool& handled, bool& cancel)->void
	global Event<void(Key key, bool pressed, bool& handled, bool& cancel)> KeyEvent;

	// OnKeyPressed(Key key, bool pressed, bool& handled, bool& cancel)->void
	global Event<void(Key key, bool& handled, bool& cancel)> KeyPressed;

	// OnKeyReleased(Key key, bool pressed, bool& handled, bool& cancel)->void
	global Event<void(Key key, bool& handled, bool& cancel)> KeyReleased;
}

#include <indxe>
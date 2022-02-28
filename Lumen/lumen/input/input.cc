#pragma once

#include <indx>

#include "key.cc"
#include "key_helper.cc"
#include "key_state.cc"

#include <indxs>

namespace Lumen::Input
{
    fun Init()->void;
    fun Deinit()->void;

    // OnKeyEvent(Key key, KeyState state, bool& handled, bool& cancel)->void
    global Event<void(Lumen::Key key, KeyState state, bool& handled, bool& cancel)> KeyEvent;

    // OnKeyPressed(Key key, bool& handled, bool& cancel)->void
    global Event<void(Lumen::Key key, bool& handled, bool& cancel)> KeyPressed;

    // OnKeyReleased(Key key, bool& handled, bool& cancel)->void
    global Event<void(Lumen::Key key, bool& handled, bool& cancel)> KeyReleased;

    // OnMouseEvent(Lumen::Key key, KeyState state, bool isMoving, Vec2I position, bool& handled, bool& cancel)->void;
    global Event<void(
        Lumen::Key key, KeyState state, bool isMoving, Vec2I position, bool& handled, bool& cancel)>
        MouseEvent;

    // OnMouseMoved(Vec2I position, bool& handled, bool& cancel)->void;
    global Event<void(Vec2I position, bool& handled, bool& cancel)> MouseMoved;

    // OnMouseMoved(bool& handled, bool& cancel)->void;
    global Event<void(Key key, bool& handled, bool& cancel)> MousePressed;

    // OnMouseMoved(bool& handled, bool& cancel)->void;
    global Event<void(Key key, bool& handled, bool& cancel)> MouseReleased;

    fun LMB()->KeyState;
    fun RMB()->KeyState;
    fun MMB()->KeyState;

    fun Key(Lumen::Key key)->KeyState;
    fun KeyDown(Lumen::Key key)->bool;
    fun KeyUp(Lumen::Key key)->bool;
    fun SetKeyState(Lumen::Key key, KeyState state)->void;

    fun SetMousePosition(Vec2I position)->void;
    fun MousePosition()->Vec2I;

    fun LastMousePosition()->Vec2I;

    fun MFP()->Vec2F;

    fun IsMFPIn(const Rect& r)->bool;
}

#include <indxe>
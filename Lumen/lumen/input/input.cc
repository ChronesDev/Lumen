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

    fun GetLMB()->KeyState;
    fun GetRMB()->KeyState;
    fun GetMMB()->KeyState;
    global INDEX_Property(get = GetLMB) KeyState LMB;
    global INDEX_Property(get = GetRMB) KeyState RMB;
    global INDEX_Property(get = GetMMB) KeyState MMB;

    fun Key(Lumen::Key key)->KeyState;
    fun KeyDown(Lumen::Key key)->bool;
    fun KeyUp(Lumen::Key key)->bool;
    fun SetKeyState(Lumen::Key key, KeyState state)->void;

    fun SetMousePosition(Vec2I position)->void;
    fun GetMousePosition()->Vec2I;
    global INDEX_Property(get = GetMousePosition) Vec2I MousePosition;

    fun GetLastMousePosition()->Vec2I;
    global INDEX_Property(get = GetLastMousePosition) Vec2I LastMousePosition;

    fun GetMFP()->Vec2F;
    global INDEX_Property(get = GetMFP) Vec2F MPF;

    fun IsMFPIn(const Rect& r)->bool;
}

#include <indxe>
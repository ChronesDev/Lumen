#include "input.cc"

#include <lumen/detour/detour.cc>
#include <lumen/log/log.cc>
#include <lumen/signature/signature.cc>

#include <indxs>

static fun OnKeyEvent_(ulong id, ulong value)->void;
static fun OnMouseEvent_(UInt64 arg1, UInt64 arg2, UInt64 arg3, UInt64 arg4, UInt64 arg5, UInt64 arg6, UInt64 arg7)
    ->void;
static fun OnMouseEvent_Other_(
    Lumen::Key key, Lumen::KeyState state, bool isMoving, Vec2I position, bool& handled, bool& cancel)
    ->void;

namespace Lumen::Input
{
    static bool Initialized_ = false;

    fun Init()->void
    {
        if (Initialized_) return;

        {
            var result = Mem.FindSignaturePtr(Signature::KeyboardEvent);
            Log("KeyboardEvent address: ", result);
            Detour::KeyEventDetour.Hook(result, Detour::KeyEventOriginal, OnKeyEvent_);
            Log("KeyboardEvent successfully hooked");
        }

        {
            var result = Mem.FindSignaturePtr(Signature::MouseEvent);
            Log("MouseEvent address: ", result);
            Detour::MouseEventDetour.Hook(result, Detour::MouseEventOriginal, OnMouseEvent_);
            Log("MouseEvent successfully hooked");
        }

        Initialized_ = true;
    }

    fun Deinit()->void
    {
        if (!Initialized_) return;

        Detour::KeyEventDetour.UnhookIfEnabled();
        Log("KeyboardEvent unhooked");

        Detour::MouseEventDetour.UnhookIfEnabled();
        Log("MouseEvent unhooked");

        Initialized_ = false;
    }

    static std::array<KeyState, 0xFF> KeySet_ = {};

    fun LMB()->KeyState { return KeySet_[(size_t)Lumen::Key::LeftButton]; }
    fun RMB()->KeyState { return KeySet_[(size_t)Lumen::Key::RightButton]; }
    fun MMB()->KeyState { return KeySet_[(size_t)Lumen::Key::MiddleButton]; }

    fun Key(Lumen::Key key)->KeyState { return KeySet_[(size_t)key]; }
    fun KeyDown(Lumen::Key key)->bool { return Key(key) == KeyState::Pressed; }
    fun KeyUp(Lumen::Key key)->bool { return Key(key) == KeyState::Released; }
    fun SetKeyState(Lumen::Key key, KeyState state)->void { KeySet_[(size_t)key] = state; }

    static Vec2I MousePosition_;
    static Vec2I LastMousePosition_;
    static Vec2F MFP_;
    static Vec2F LastMFP_;

    fun SetMousePosition(Vec2I position)->void
    {
        LastMousePosition_ = MousePosition_;
        MousePosition_ = position;
        LastMFP_ = MFP_;
        MFP_ = { (float)position.X, (float)position.Y };
    }
    fun MousePosition()->Vec2I { return MousePosition_; }

    fun LastMousePosition()->Vec2I { return LastMousePosition_; }

    fun MFP()->Vec2F { return MFP_; }

    fun IsMFPIn(const Rect& r)->bool { return r.IsPointInside(MFP_); }
}

static fun OnKeyEvent_(ulong id, ulong value)->void
{
    using namespace Lumen;

    var lastKeyState = Lumen::Input::Key((Lumen::Key)id);
    Lumen::Input::SetKeyState((Lumen::Key)id, value ? KeyState::Pressed : KeyState::Released);

    var key = (Lumen::Key)id;
    var keyState = value ? KeyState::Pressed : KeyState::Released;
    var handled = false;
    var cancel = false;

    for (var& v : Lumen::Input::KeyEvent)
    {
        v(key, keyState, handled, cancel);
        if (handled) return;
    }
    if (cancel)
    {
        Lumen::Input::SetKeyState((Lumen::Key)id, lastKeyState);
        return;
    }

    Lumen::Detour::KeyEventOriginal(id, value);
}

static fun OnMouseEvent_(UInt64 arg1, UInt64 arg2, UInt64 arg3, UInt64 arg4, UInt64 arg5, UInt64 arg6, UInt64 arg7)
    ->void
{
    using namespace Lumen;

    int mouseButton = arg2;
    bool isMouseButton = arg2 != 0;
    KeyState state = !isMouseButton ? KeyState::Unknown : (arg3 == 1 ? KeyState::Pressed : KeyState::Released);

    bool isPressed = arg3 == 1;
    bool isReleased = arg3 == 0 && arg2 != 0;
    bool isMoving = arg3 == 0 && arg2 == 0;

    int mouseX = (int)*reinterpret_cast<short*>(&arg4);
    int mouseY = (int)*reinterpret_cast<short*>(&arg5);

    Lumen::Key key = !isMouseButton ? Lumen::Key::Null
        : mouseButton == 1          ? Lumen::Key::LeftButton
        : mouseButton == 2          ? Lumen::Key::RightButton
                                    : Lumen::Key::Null;

    bool handled = false;
    bool cancel = false;

    for (var& v : Lumen::Input::MouseEvent)
    {
        v(key, state, isMoving, { mouseX, mouseY }, handled, cancel);
        if (handled) return;
    }
    if (cancel) return;

    OnMouseEvent_Other_(key, state, isMoving, { mouseX, mouseY }, handled, cancel);
    if (handled) return;
    if (cancel) return;

    Lumen::Detour::MouseEventOriginal(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
}

static fun OnMouseEvent_Other_(
    Lumen::Key key, Lumen::KeyState state, bool isMoving, Vec2I position, bool& handled, bool& cancel)
    ->void
{
    using namespace Lumen;

    if (isMoving)
    {
        var lastPosition = Lumen::Input::MousePosition_;
        var lastLastPosition = Lumen::Input::LastMousePosition_;
        Lumen::Input::SetMousePosition(position);

        for (var& v : Lumen::Input::MouseMoved)
        {
            v(position, handled, cancel);
            if (handled) break;
        }

        if (cancel)
        {
            Lumen::Input::SetMousePosition(lastLastPosition);
            Lumen::Input::SetMousePosition(lastPosition);
        }
    }
    else
    {
        var lastKeyState = Lumen::Input::Key(key);
        Lumen::Input::SetKeyState(key, state);

        if (state == KeyState::Pressed)
        {
            for (var& v : Lumen::Input::MousePressed)
            {
                v(key, handled, cancel);
                if (handled) break;
            }
        }

        elif (state == KeyState::Released)
        {
            for (var& v : Lumen::Input::MouseReleased)
            {
                v(key, handled, cancel);
                if (handled) break;
            }
        }

        if (cancel) Lumen::Input::SetKeyState(key, lastKeyState);
    }
}

#include <indxe>
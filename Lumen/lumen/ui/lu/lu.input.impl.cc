#include <Unknwn.h>
#include <winrt/base.h>
#include <winrt/windows.ui.core.h>
#include <winrt/windows.ui.composition.core.h>
#include <winrt/windows.ui.input.h>
#include <winrt/windows.ui.xaml.h>
#include <winrt/windows.foundation.h>
#include <winrt/windows.applicationmodel.core.h>

#include <lumen/input/input.cc>
#include <lumen/ui/lui/lui.cc>

#include "lu.cc"

#include <indxs>

namespace Lumen::UI
{
    extern IPtr<LUIContext> LContext;

    static fun OnKeyEvent_(Lumen::Key key, KeyState state, bool& handled, bool& cancel)
    {
        if (!LContext) return;
        if (state == KeyState::Pressed) { LContext->TriggerKeyPressed(key); }
        elif (state == KeyState::Released) { LContext->TriggerKeyReleased(key); }
        if (LContext->HasCapturedInput)
        {
            handled = true;
            cancel = true;
        }
    }
    static fun OnMouseMoved_(Vec2I position, bool& handled, bool& cancel)
    {
        if (!LContext) return;
        LContext->TriggerMouseMove({ (float)position.X, (float)position.Y });
    }
    static fun OnMousePressed_(Key key, bool& handled, bool& cancel) { OnKeyEvent_(key, KeyState::Pressed, handled, cancel);  }
    static fun OnMouseReleased_(Key key, bool& handled, bool& cancel) { OnKeyEvent_(key, KeyState::Released, handled, cancel);  }

    fun InitInput()->void
    {
        Input::KeyEvent.Add(OnKeyEvent_);
        Input::MouseMoved.Add(OnMouseMoved_);
        Input::MousePressed.Add(OnMousePressed_);
        Input::MouseReleased.Add(OnMouseReleased_);
    }
    fun DeinitInput()->void
    {
        Input::KeyEvent.Remove(OnKeyEvent_);
        Input::MouseMoved.Remove(OnMouseMoved_);
        Input::MousePressed.Remove(OnMousePressed_);
        Input::MouseReleased.Remove(OnMouseReleased_);
    }
}

#include <indxe>
#include "WindowList.h"
#include <WindowServer/WSAPITypes.h>
#include <LibGUI/GEventLoop.h>

Window& WindowList::ensure_window(const WindowIdentifier& identifier)
{
    auto it = m_windows.find(identifier);
    if (it != m_windows.end())
        return *it->value;
    auto window = make<Window>(identifier);
    window->set_button(aid_create_button());
    window->button()->on_click = [identifier] (GButton&) {
        WSAPI_ClientMessage message;
        message.type = WSAPI_ClientMessage::Type::WM_SetActiveWindow;
        message.wm.client_id = identifier.client_id();
        message.wm.window_id = identifier.window_id();
        bool success = GEventLoop::post_message_to_server(message);
        ASSERT(success);
    };
    auto& window_ref = *window;
    m_windows.set(identifier, move(window));
    return window_ref;
}

void WindowList::remove_window(const WindowIdentifier& identifier)
{
    m_windows.remove(identifier);
}

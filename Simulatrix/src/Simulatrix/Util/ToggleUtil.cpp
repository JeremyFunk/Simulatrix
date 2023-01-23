#include "simixpch.h"
#include "ToggleUtil.h"

namespace Simulatrix {
    void ToggleUtil::RegisterToggle(KeyCode key, std::function<bool(bool)> fn) {
        m_RegisteredToggles.push_back(ToggleData(key, fn));
    }
    void ToggleUtil::RegisterStatelessToggle(KeyCode key, std::function<bool()> fn) {
        m_RegisteredStatelessToggles.push_back(StatelessToggleData(key, fn));
    }
    bool ToggleUtil::OnKeyPressed(KeyPressedEvent& e) {
        if (e.IsRepeat())
            return false;
        for (auto& t : m_RegisteredToggles) {
            if (t.Key == e.GetKeyCode()) {
                t.Pressed = !t.Pressed;
                return t.Trigger(t.Pressed);
            }
        }
        for (auto& t : m_RegisteredStatelessToggles) {
            if (t.Key == e.GetKeyCode()) {
                return t.Trigger();
            }
        }
    }
}
#pragma once
#include <Simulatrix/Core/KeyCode.h>
#include <Simulatrix/Events/KeyEvent.h>

namespace Simulatrix {
    struct ToggleData {
        KeyCode Key;
        bool Pressed;
        std::function<bool(bool)> Trigger;

        ToggleData(KeyCode key, std::function<bool(bool)> trigger) : Key(key), Trigger(trigger), Pressed(false) {

        }
    };

    class ToggleUtil {
    public:
        void RegisterToggle(KeyCode key, std::function<bool(bool)> trigger);
        bool OnKeyPressed(KeyPressedEvent& e);
    private:
        std::vector<ToggleData> m_RegisteredToggles;
    };
}
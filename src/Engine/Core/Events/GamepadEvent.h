#pragma once

#include "Engine/Core/Events/Event.h"
#include "Engine/Core/Events/Codes/GamePadCodes.h"

namespace Shell {
    class GamepadEvent : public Event {
    public:
        [[nodiscard]] Gamepad::ButtonCodeEnum GetKeyCode() const { return m_KeyCode; }

        EVENT_CLASS_CATEGORY(EventCategoryGamepad | EventCategoryInput)
    protected:
        GamepadEvent(const Gamepad::ButtonCodeEnum keycode)
                : m_KeyCode(keycode) {}

        Gamepad::ButtonCodeEnum m_KeyCode;
    };

    class GamepadButtonPressedEvent : public GamepadEvent
    {
    public:
        GamepadButtonPressedEvent(const Gamepad::ButtonCodeEnum keycode)
                : GamepadEvent(keycode) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "GamepadButtonPressedEvent: " << m_KeyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(GamepadButtonPressed)
    };

    class GamepadButtonReleasedEvent : public GamepadEvent
    {
    public:
        GamepadButtonReleasedEvent(const Gamepad::ButtonCodeEnum keycode)
                : GamepadEvent(keycode) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "GamepadButtonReleasedEvent: " << m_KeyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(GamepadButtonReleased)
    };
}
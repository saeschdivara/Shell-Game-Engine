#pragma once

#include "Engine/Core/Events/Codes/KeyCodes.h"
#include "Engine/Core/Events/Codes/MouseCodes.h"

namespace Shell {
    class InputService {
    public:
        // keyboard
        inline static bool IsKeyPressed(Key::KeyCodeEnum code) { return m_Instance->IsKeyPressedImpl(code); }

        // mouse
        inline static bool IsMouseButtonPressed(Mouse::MouseButtonEnum code) { return m_Instance->IsMouseButtonPressedImpl(code); }
        inline static std::pair<float, float> GetMousePosition() { return m_Instance->GetMousePositionImpl(); }
        inline static float GetMouseX() { return m_Instance->GetMouseXImpl(); }
        inline static float GetMouseY() { return m_Instance->GetMouseYImpl(); }

        // TODO: add gamepad

    protected:
        // keyboard
        virtual bool IsKeyPressedImpl(Key::KeyCodeEnum code) = 0;

        // mouse
        virtual bool IsMouseButtonPressedImpl(Mouse::MouseButtonEnum code) = 0;
        virtual std::pair<float, float> GetMousePositionImpl() = 0;
        virtual float GetMouseXImpl() = 0;
        virtual float GetMouseYImpl() = 0;

    private:
        static InputService* m_Instance;
    };
}
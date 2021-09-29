#include "MacOSInputService.h"
#include "Engine/Core/Application.h"
#include <GLFW/glfw3.h>

namespace Shell {

    InputService *InputService::m_Instance = new MacOSInputService;

    bool MacOSInputService::IsKeyPressedImpl(Key::KeyCodeEnum code) {
        auto window = static_cast<GLFWwindow *>(Application::Instance()->GetWindow()->GetNativeWindow());
        auto state = glfwGetKey(window, code);

        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool MacOSInputService::IsMouseButtonPressedImpl(Mouse::MouseButtonEnum code) {
        auto window = static_cast<GLFWwindow *>(Application::Instance()->GetWindow()->GetNativeWindow());
        auto state = glfwGetMouseButton(window, code);

        return state == GLFW_PRESS;
    }

    std::pair<float, float> MacOSInputService::GetMousePositionImpl() {
        auto window = static_cast<GLFWwindow *>(Application::Instance()->GetWindow()->GetNativeWindow());
        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);

        return { xPos, yPos };
    }

    float MacOSInputService::GetMouseXImpl() {
        auto [x, y] = GetMousePositionImpl();
        return x;
    }

    float MacOSInputService::GetMouseYImpl() {
        auto [x, y] = GetMousePositionImpl();
        return y;
    }

    bool MacOSInputService::IsGamepadButtonPressedImpl(Gamepad::ButtonCodeEnum code) {
        if (glfwJoystickPresent(GLFW_JOYSTICK_1) == GLFW_FALSE) {
            return false;
        }

        GLFWgamepadstate state;
        glfwGetGamepadState(GLFW_JOYSTICK_1, &state);

        return state.buttons[static_cast<uint16_t>(code)] == GLFW_PRESS;
    }

    float MacOSInputService::GetGamepadAxisImpl(Gamepad::AxisCodeEnum code) {
        if (glfwJoystickPresent(GLFW_JOYSTICK_1) == GLFW_FALSE) {
            return 0.0f;
        }

        GLFWgamepadstate state;
        glfwGetGamepadState(GLFW_JOYSTICK_1, &state);

        return state.axes[static_cast<uint8_t>(code)];
    }
}

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
}

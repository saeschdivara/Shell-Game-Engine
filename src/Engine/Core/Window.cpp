#include "Engine/Core/Window.h"
#include "Engine/Core/Profiling.h"
#include "Engine/Core/Events/ApplicationEvent.h"
#include "Engine/Core/Events/KeyEvent.h"
#include "Engine/Core/Events/MouseEvent.h"

#include "Platform/Rendering/OpenGL/OpenGLContext.h"

#include <GLFW/glfw3.h>

namespace Shell {
    void Window::Init() {
        OPTICK_EVENT();

        /* Initialize the library */
        if (!glfwInit()) {
            SHELL_CORE_ERROR("GLFW could not be initialised");
            return;
        }

#ifdef __APPLE__
        /* We need to explicitly ask for a 3.2 context on OS X */
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

        m_Data.Height = 720;
        m_Data.Width = 1280;

        /* Create a windowed mode window and its OpenGL context */
        m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, "Shell Engine", NULL, NULL);
        if (!m_Window) {
            SHELL_CORE_ERROR("Window could not be initialised");
            glfwTerminate();
            return;
        }

        m_Context = new OpenGLContext(m_Window);
        m_Context->Init();
    }

    void Window::OnUpdate() {
        OPTICK_EVENT();

        /* Poll for and process events */
        glfwPollEvents();

        m_Context->SwapBuffers();
    }

    void Window::SetupCallbacks(const Window::EventCallbackFn &callback) {
        OPTICK_EVENT();

        m_Data.Callback = callback;

        glfwSetWindowUserPointer(m_Window, &m_Data);

        glfwSetKeyCallback(m_Window, [](GLFWwindow * window, int key, int scancode, int action, int mods) {
            auto dataPointer = static_cast<Window::WindowData *>(glfwGetWindowUserPointer(window));

            if (action == GLFW_PRESS) {
                KeyPressedEvent event(key, 0);
                dataPointer->Callback(event);
            }
            else if (action == GLFW_RELEASE) {
                KeyReleasedEvent event(key);
                dataPointer->Callback(event);
            }
            else if (action == GLFW_REPEAT) {
                KeyPressedEvent event(key, 1);
                dataPointer->Callback(event);
            }
        });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow * window,  int button, int action, int mods) {
            auto dataPointer = static_cast<Window::WindowData *>(glfwGetWindowUserPointer(window));

            if (action == GLFW_PRESS) {
                MouseButtonPressedEvent event(button);
                dataPointer->Callback(event);
            }
            else if (action == GLFW_RELEASE) {
                MouseButtonReleasedEvent event(button);
                dataPointer->Callback(event);
            }

        });

        glfwSetScrollCallback(m_Window, [](GLFWwindow *window, double xOffset, double yOffset) {
            auto dataPointer = static_cast<Window::WindowData *>(glfwGetWindowUserPointer(window));

            MouseScrolledEvent event(xOffset, yOffset);
            dataPointer->Callback(event);
        });

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow *window, double xPos, double yPos) {
            auto dataPointer = static_cast<Window::WindowData *>(glfwGetWindowUserPointer(window));

            MouseMovedEvent event((float) xPos, (float)yPos);
            dataPointer->Callback(event);
        });

        // Set GLFW callbacks
        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            data.Width = width;
            data.Height = height;

            WindowResizeEvent event(width, height);
            data.Callback(event);
        });

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            WindowCloseEvent event;
            data.Callback(event);
        });
    }

    void Window::SetTitle(const std::string &title) {
        OPTICK_EVENT();

        glfwSetWindowTitle(m_Window, title.c_str());
    }
}
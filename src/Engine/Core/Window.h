#pragma once

#include "Engine/Core/Events/Event.h"

class GLFWwindow;

namespace Shell {

    class Window {
    public:
        using EventCallbackFn = std::function<void(Event&)>;

        virtual void Init();
        virtual void Render();
        virtual void OnUpdate();

        virtual void SetupCallbacks(const EventCallbackFn& callback);

    protected:
        GLFWwindow* m_Window;

        struct WindowData {
            Window::EventCallbackFn Callback;
        };

        WindowData m_Data;
    };

}

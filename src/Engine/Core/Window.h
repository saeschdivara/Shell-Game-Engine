#pragma once

#include "Engine/Core/Events/Event.h"

class GLFWwindow;

namespace Shell {

    class Window {
    public:
        using EventCallbackFn = std::function<void(Event&)>;

        virtual void Init();
        virtual void OnUpdate();

        virtual void SetupCallbacks(const EventCallbackFn& callback);

        uint32_t GetHeight() const { return m_Data.Height; }
        uint32_t GetWidth() const { return m_Data.Width; }
        void* GetNativeWindow() { return m_Window; }

    protected:
        GLFWwindow* m_Window;

        struct WindowData {
            unsigned int Width, Height;
            Window::EventCallbackFn Callback;
        };

        WindowData m_Data;
    };

}

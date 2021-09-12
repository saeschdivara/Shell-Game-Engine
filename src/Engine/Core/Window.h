#pragma once

class GLFWwindow;

namespace Shell {
    class Window {
    public:
        virtual void Init();
        virtual void Render();
        virtual void OnUpdate();

    protected:
        GLFWwindow* m_window;
    };
}

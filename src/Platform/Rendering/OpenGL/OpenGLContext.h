#pragma once

#include "Engine/Core/Rendering/GraphicsContext.h"

struct GLFWwindow;

namespace Shell {

    class OpenGLContext : public GraphicsContext {
    public:
        OpenGLContext(GLFWwindow* windowHandle);

        void Init() override;
        void SwapBuffers() override;

    private:
        GLFWwindow* m_WindowHandle;
    };

}



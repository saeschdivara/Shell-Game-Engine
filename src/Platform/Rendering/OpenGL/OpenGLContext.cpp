#include "OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Shell {

    OpenGLContext::OpenGLContext(GLFWwindow *windowHandle) : m_WindowHandle(windowHandle) {
    }

    void OpenGLContext::Init() {
        /* Make the window's context current */
        glfwMakeContextCurrent(m_WindowHandle);
        gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

        SHELL_CORE_INFO(glGetString(GL_VERSION));
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void OpenGLContext::SwapBuffers() {
        /* Swap front and back buffers */
        glfwSwapBuffers(m_WindowHandle);
    }
}
#include "Renderer.h"

#include <glad/glad.h>

namespace Shell {

    Scope<Renderer> Renderer::m_Instance;

    Scope<Renderer>& Renderer::Instance() {

        if (!m_Instance) {
            m_Instance = Create();
        }

        return m_Instance;
    }

    Scope<Renderer> Renderer::Create() {
        auto instance = CreateScope<Renderer>();

        instance->m_API = RenderAPI::OpenGL;

        return instance;
    }
}
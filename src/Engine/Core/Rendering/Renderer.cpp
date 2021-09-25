#include "Renderer.h"
#include "Engine/Core/Rendering/RenderCommand.h"

namespace Shell {

    Scope<Renderer> Renderer::m_Instance;

    Scope<Renderer>& Renderer::Instance() {

        if (!m_Instance) {
            m_Instance = Create();
        }

        return m_Instance;
    }

    void Renderer::BeginScene() {
    }

    void Renderer::EndScene() {
    }

    void Renderer::Submit(const Ref<BufferContainer> &bufferContainer) {
        bufferContainer->Bind();
        RenderCommand::Create()->DrawIndexed(bufferContainer);
    }

    Scope<Renderer> Renderer::Create() {
        auto instance = CreateScope<Renderer>();

        instance->m_API = RenderAPI::OpenGL;

        return instance;
    }
}
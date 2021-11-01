#include "Renderer.h"
#include "Engine/Core/Profiling.h"
#include "Engine/Core/Rendering/RenderCommand.h"

namespace Shell {

    Scope<Renderer> Renderer::m_Instance;

    Scope<Renderer>& Renderer::Instance() {

        if (!m_Instance) {
            m_Instance = Create();
        }

        return m_Instance;
    }

    void Renderer::BeginScene(Ref<OrthographicCamera> camera) {
        m_Camera = camera;
    }

    void Renderer::EndScene() {
    }

    void Renderer::Submit(const Ref<BufferContainer> &bufferContainer, const Ref<Shader>& shader, const glm::mat4 & transform) {
        OPTICK_EVENT();

        shader->Bind();
        shader->SetUniform("u_ViewProjection", m_Camera->GetViewProjectionMatrix());
        shader->SetUniform("u_ModelTransform", transform);

        bufferContainer->Bind();
        RenderCommand::Create()->DrawIndexed(bufferContainer);
    }

    Scope<Renderer> Renderer::Create() {
        OPTICK_EVENT();

        auto instance = CreateScope<Renderer>();

        instance->m_API = RenderAPI::OpenGL;

        return instance;
    }
}
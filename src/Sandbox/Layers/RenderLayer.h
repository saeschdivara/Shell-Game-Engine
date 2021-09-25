#pragma once

#include <Engine/Core/Layers/Layer.h>
#include <Engine/Core/Rendering/BufferContainer.h>
#include <Engine/Core/Rendering/Camera.h>
#include <Engine/Core/Rendering/Renderer.h>
#include <Engine/Core/Rendering/RenderCommand.h>
#include <Engine/Core/Rendering/Shader.h>

namespace Sandbox {
    class RenderLayer : public Shell::Layer {
    public:
        RenderLayer() :
            Layer("Render Layer"),
            m_ClearColor(glm::vec4(0.2f, 0.2f, 0.2f, 1)),
            m_Camera(new Shell::OrthographicCamera(-1.6f, 1.6f, -0.9f, 0.9f))
            {}

        void OnAttach() override;
        void OnUpdate() override;

    private:
        glm::vec4 m_ClearColor;
        Shell::Ref<Shell::BufferContainer> m_BufferContainer;
        Shell::Ref<Shell::Shader> m_Shader;

        Shell::Ref<Shell::OrthographicCamera> m_Camera;
    };

}
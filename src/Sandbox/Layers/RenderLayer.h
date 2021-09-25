#pragma once

#include <Engine/Core/Layers/Layer.h>
#include <Engine/Core/Rendering/BufferContainer.h>
#include <Engine/Core/Rendering/Renderer.h>
#include <Engine/Core/Rendering/RenderCommand.h>
#include <Engine/Core/Rendering/Shader.h>

namespace Sandbox {
    class RenderLayer : public Shell::Layer {
    public:
        RenderLayer() :
            Layer("Render Layer"),
            m_ClearColor(glm::vec4(0.2f, 0.2f, 0.2f, 1))
            {}

        void OnAttach() override {

            m_BufferContainer = Shell::BufferContainer::Create();

            float vertices [] = {
                    -0.5f, -0.5f, 0.0f, 0.3f, 0.3f, 1.0f, 1.0f,
                    0.5f, -0.5f, 0.0f, 0.3f, 0.7f, 0.2f, 1.0f,
                    0.0f,  0.5f, 0.0f, 1.0f, 0.3f, 1.0f, 1.0f
            };

            auto m_VertexBuffer = Shell::VertexBuffer::Create(vertices, sizeof(vertices));

            Shell::BufferLayout layout = {
                    { Shell::ShaderDataType::Float3, "a_Position" },
                    { Shell::ShaderDataType::Float4, "a_Color" },
            };

            m_VertexBuffer->SetLayout(layout);
            m_BufferContainer->AddBuffer(m_VertexBuffer);

            uint32_t indices[3] = { 0, 1, 2 };
            auto m_IndexBuffer = Shell::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
            m_BufferContainer->AddBuffer(m_IndexBuffer);

            std::string vertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;

            out vec4 v_Color;

            void main()
            {
                v_Color = a_Color;
                gl_Position = vec4(a_Position, 1.0);
            }
        )";

            std::string fragmentSrc = R"(
            #version 330 core
            layout(location = 0) out vec4 color;

            in vec4 v_Color;

            void main()
            {
                color = v_Color;
            }
        )";

            m_Shader = Shell::CreateScope<Shell::Shader>(vertexSrc, fragmentSrc);
        };

        void OnUpdate() override {
            Shell::RenderCommand::Create()->SetClearColor(m_ClearColor);
            Shell::RenderCommand::Create()->Clear();

            Shell::Renderer::Instance()->BeginScene();

            m_Shader->Bind();
            Shell::Renderer::Instance()->Submit(m_BufferContainer);

            Shell::Renderer::Instance()->EndScene();
        };

    private:
        glm::vec4 m_ClearColor;
        Shell::Ref<Shell::BufferContainer> m_BufferContainer;
        Shell::Scope<Shell::Shader> m_Shader;

    };

}
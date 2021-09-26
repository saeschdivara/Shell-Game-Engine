#include "RenderLayer.h"

#include <Engine/Core/InputService.h>
#include <glm/ext.hpp>

namespace Sandbox {
    void RenderLayer::OnAttach() {
        m_BufferContainer = Shell::BufferContainer::Create();

        float vertices [] = {
                //x      y      z
                -0.5f, -0.5f, 0.0f, 0.3f, 0.3f, 1.0f, 1.0f,
                 0.5f, -0.5f, 0.0f, 0.3f, 0.3f, 1.0f, 1.0f,
                 0.5f,  0.5f, 0.0f, 0.0f, 0.3f, 1.0f, 1.0f,
                -0.5f,  0.5f, 0.0f, 0.0f, 0.3f, 1.0f, 1.0f,
        };

        auto m_VertexBuffer = Shell::VertexBuffer::Create(vertices, sizeof(vertices));

        Shell::BufferLayout layout = {
                { Shell::ShaderDataType::Float3, "a_Position" },
                { Shell::ShaderDataType::Float4, "a_Color" },
        };

        m_VertexBuffer->SetLayout(layout);
        m_BufferContainer->AddBuffer(m_VertexBuffer);

        uint32_t indices[] = { 0, 1, 2, 2, 3, 0 };
        auto m_IndexBuffer = Shell::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
        m_BufferContainer->AddBuffer(m_IndexBuffer);

        std::string vertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;

            uniform mat4 u_ViewProjection;
            uniform mat4 u_ModelTransform;

            out vec4 v_Color;

            void main()
            {
                v_Color = a_Color;
                gl_Position = u_ViewProjection * u_ModelTransform * vec4(a_Position, 1.0);
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

        m_Shader = Shell::CreateRef<Shell::Shader>(vertexSrc, fragmentSrc);
    }

    void RenderLayer::OnUpdate(std::chrono::milliseconds deltaTime) {
        UpdateCameraWithMovement(deltaTime);

        Shell::RenderCommand::Create()->SetClearColor(m_ClearColor);
        Shell::RenderCommand::Create()->Clear();

        Shell::Renderer::Instance()->BeginScene(m_Camera);

        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

        for (int y = 0; y < 20; y++)
        {
            for (int x = 0; x < 20; x++)
            {
                glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
                glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
                Shell::Renderer::Instance()->Submit(m_BufferContainer, m_Shader, transform);
            }
        }

        Shell::Renderer::Instance()->EndScene();
    }

    void RenderLayer::UpdateCameraWithMovement(std::chrono::milliseconds deltaTime) {
        if (Shell::InputService::IsKeyPressed(Shell::Key::Left)) {
            m_CameraPosition.x += m_CameraSpeed * deltaTime.count();
            m_Camera->SetPosition(m_CameraPosition);
        }
        else if (Shell::InputService::IsKeyPressed(Shell::Key::Right)) {
            m_CameraPosition.x -= m_CameraSpeed * deltaTime.count();
            m_Camera->SetPosition(m_CameraPosition);
        }
        else if (Shell::InputService::IsKeyPressed(Shell::Key::Up)) {
            m_CameraPosition.y += m_CameraSpeed * deltaTime.count();
            m_Camera->SetPosition(m_CameraPosition);
        }
        else if (Shell::InputService::IsKeyPressed(Shell::Key::Down)) {
            m_CameraPosition.y -= m_CameraSpeed * deltaTime.count();
            m_Camera->SetPosition(m_CameraPosition);
        }
    }
}
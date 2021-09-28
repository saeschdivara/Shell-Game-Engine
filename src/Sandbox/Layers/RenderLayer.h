#pragma once

#include <Engine/Core/Layers/Layer.h>
#include <Engine/Core/Rendering/BufferContainer.h>
#include <Engine/Core/Rendering/Camera.h>
#include <Engine/Core/Rendering/Renderer.h>
#include <Engine/Core/Rendering/RenderCommand.h>
#include <Engine/Core/Rendering/Shader.h>
#include <Engine/Core/Rendering/Texture.h>

namespace Sandbox {
    class RenderLayer : public Shell::Layer {
    public:
        RenderLayer() :
            Layer("Render Layer"),
            m_ClearColor(glm::vec4(0.2f, 0.2f, 0.2f, 1)),
            m_Camera(new Shell::OrthographicCamera(-1.6f, 1.6f, -0.9f, 0.9f))
            {}

        void OnAttach() override;
        void OnUpdate(std::chrono::milliseconds deltaTime) override;

    private:
        void UpdateCameraWithMovement(std::chrono::milliseconds deltaTime);

    private:
        glm::vec4 m_ClearColor;

        Shell::Ref<Shell::BufferContainer> m_BufferContainer;
        Shell::Ref<Shell::Shader> m_Shader;

        Shell::Ref<Shell::BufferContainer> m_BufferContainerWithTextures;
        Shell::Ref<Shell::Shader> m_TexturedShader;

        Shell::Ref<Shell::Texture2D> m_Texture;

        Shell::Ref<Shell::OrthographicCamera> m_Camera;
        glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
        float m_CameraSpeed = 0.008f;
    };

}
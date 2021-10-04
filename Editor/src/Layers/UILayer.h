#pragma once

#include <Engine/Core/Layers/Layer.h>
#include <Engine/Core/Rendering/Buffer.h>
#include <Engine/Core/Rendering/BufferContainer.h>
#include <Engine/Core/Rendering/Camera.h>
#include <Engine/Core/Rendering/FrameBuffer.h>
#include <Engine/Core/Rendering/Shader.h>
#include <Engine/Core/Rendering/Texture.h>
#include <Engine/Project/SceneBlueprint.h>
#include <Engine/Project/Entities/EntityManager.h>

#include <glm/glm.hpp>

namespace Shell::Editor {

    class EditorUILayer : public Layer {
    public:
        EditorUILayer();

        void OnAttach() override;
        void OnUpdate(std::chrono::milliseconds deltaTime) override;
        void OnUiRender() override;

    private:
        Ref<EntityManager> m_EntityManager;
        Ref<SceneBlueprint> m_CurrentSceneBluePrint;

        // ------ Rendering ------
        Ref<FrameBuffer> m_Framebuffer;

        Shell::Ref<Shell::BufferContainer> m_BufferContainerWithTextures;
        Shell::Ref<Shell::Shader> m_TexturedShader;

        Shell::Ref<Shell::OrthographicCamera> m_Camera;

        glm::vec4 m_ClearColor;

        // ------ UI ------

        bool m_ViewportFocused = false;
        bool m_ViewportHovered = false;

        glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
        glm::vec2 m_ViewportBounds[2];
    };

}
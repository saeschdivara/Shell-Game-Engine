#pragma once

#include <Engine/Core/Layers/Layer.h>
#include <Engine/Core/Rendering/FrameBuffer.h>
#include <Engine/Project/SceneBlueprint.h>

#include <glm/glm.hpp>

namespace Shell::Editor {

    class EditorUILayer : public Layer {
    public:
        EditorUILayer();

        void OnAttach() override;
        void OnUpdate(std::chrono::milliseconds deltaTime) override;
        void OnUiRender() override;

    private:
        Ref<SceneBlueprint> m_CurrentSceneBluePrint;

        // ------ Rendering ------
        Ref<FrameBuffer> m_Framebuffer;

        glm::vec4 m_ClearColor;

        // ------ UI ------

        bool m_ViewportFocused = false;
        bool m_ViewportHovered = false;

        glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
        glm::vec2 m_ViewportBounds[2];
    };

}
#pragma once

#include "Events/EditorEvents.h"
#include "UI/Panel/Panel.h"

#include <Engine/Core/Layers/Layer.h>
#include <Engine/Core/Rendering/Buffer.h>
#include <Engine/Core/Rendering/BufferContainer.h>
#include <Engine/Core/Rendering/Camera.h>
#include <Engine/Core/Rendering/FrameBuffer.h>
#include <Engine/Core/Rendering/RenderQueue.h>
#include <Engine/Core/Rendering/Shader.h>
#include <Engine/Core/Rendering/Texture.h>
#include <Engine/Project/SceneBlueprint.h>
#include <Engine/Project/Entities/EntityManager.h>

#include <glm/glm.hpp>

struct ImRect;

namespace Shell::Editor {

    struct UIState {
        Ref<EntityManager> EntityManager;

        Project * Project = nullptr;
        Ref<SceneBlueprint> CurrentSceneBluePrint;

        SceneEntity * SelectedEntity = nullptr;
        bool ChangedEntity = false;
    };

    class EditorUILayer : public Layer {
    public:
        EditorUILayer();

        virtual ~EditorUILayer();

        void OnAttach() override;
        void OnUpdate(std::chrono::milliseconds deltaTime) override;
        void OnUiRender() override;

        void OnEvent(Event &event) override;

    private:
        void RenderMenu();
        ImRect RenderTree(SceneEntity * entity);

        bool OnCreateEntityEvent(CreateEntityEvent & event);
        bool OnSaveProjectEvent(SaveProjectEvent & event);
        bool OnLoadProjectEvent(LoadProjectEvent & event);
        bool OnSaveSceneEvent(SaveSceneEvent & event);

    private:
        // ------ Rendering ------
        Ref<FrameBuffer> m_Framebuffer;
        Ref<RenderQueue> m_RenderQueue;

        Ref<OrthographicCamera> m_Camera;

        glm::vec4 m_ClearColor;

        std::vector<Panel *> m_Panels;

        // ------ Tooling ------
        UIState m_UiState;

        // ------ UI ------

        bool m_ViewportFocused = false;
        bool m_ViewportHovered = false;

        glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
        glm::vec2 m_ViewportBounds[2];
    };

}
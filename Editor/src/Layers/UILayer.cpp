#include "UILayer.h"

#include <Engine/Core/Rendering/RenderCommand.h>
#include <Engine/Core/Rendering/Renderer.h>
#include <Engine/Project/Entities/Components.h>

#include <imgui.h>
#include <imgui_internal.h>

namespace Shell::Editor {

    EditorUILayer::EditorUILayer()
    : Layer("UI Layer"),
      m_ClearColor(glm::vec4(0.2f, 0.2f, 0.2f, 1)),
      m_Camera(new Shell::OrthographicCamera(-1.6f, 1.6f, -0.9f, 0.9f))
    {}

    void EditorUILayer::OnAttach() {
        FrameBufferSpecification frameBufferSpec;
        frameBufferSpec.Width = 1280;
        frameBufferSpec.Height = 720;

        m_Framebuffer = FrameBuffer::Create(frameBufferSpec);
        m_RenderQueue = CreateRef<RenderQueue>();
        m_RenderQueue->Init();

        m_CurrentSceneBluePrint = CreateRef<SceneBlueprint>();
        m_EntityManager = CreateRef<EntityManager>();

        auto entity = m_EntityManager->CreateEntity(m_CurrentSceneBluePrint);
        m_EntityManager->AddComponent<SpriteComponent>(entity, Texture2D::Create("./assets/textures/Checkerboard.png"));
    }

    void EditorUILayer::OnUpdate(std::chrono::milliseconds deltaTime) {
        m_Framebuffer->Bind();

        Shell::RenderCommand::Create()->SetClearColor(m_ClearColor);
        Shell::RenderCommand::Create()->Clear();

        Shell::Renderer::Instance()->BeginScene(m_Camera);

        m_RenderQueue->StartBatch();

        auto view = m_EntityManager->GetComponentView<TransformComponent, SpriteComponent>();
        for(auto &&[entity, transform, sprite] : view.each()) {
            if (sprite.Texture) {
                m_RenderQueue->EnqueueTexturedQuad(sprite.Texture, transform.GetTransform());
            }
        }

        m_RenderQueue->Flush();

        Shell::Renderer::Instance()->EndScene();

        m_Framebuffer->Unbind();
    }

    void EditorUILayer::OnUiRender() {
        // Note: Switch this to true to enable dockspace
        static bool dockspaceOpen = true;
        static bool opt_fullscreen_persistant = true;
        bool opt_fullscreen = opt_fullscreen_persistant;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen)
        {
            ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->Pos);
            ImGui::SetNextWindowSize(viewport->Size);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
        ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // DockSpace
        ImGuiIO& io = ImGui::GetIO();
        ImGuiStyle& style = ImGui::GetStyle();
        float minWinSizeX = style.WindowMinSize.x;
        style.WindowMinSize.x = 370.0f;
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        style.WindowMinSize.x = minWinSizeX;

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                // Disabling fullscreen would allow the window to be moved to the front of other windows,
                // which we can't undo at the moment without finer window depth/z control.
                //ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);1
                if (ImGui::MenuItem("New", "Ctrl+N"))
                {}

                if (ImGui::MenuItem("Open...", "Ctrl+O"))
                {}

                if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S"))
                {}

                if (ImGui::MenuItem("Exit")) {}

                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }

//        m_SceneHierarchyPanel.OnImGuiRender();
//        m_ContentBrowserPanel.OnImGuiRender();

        ImGui::Begin("Stats");

        std::string name = "None";
//        if (m_HoveredEntity)
//            name = m_HoveredEntity.GetComponent<TagComponent>().Tag;
        ImGui::Text("Hovered Entity: %s", name.c_str());

//        auto stats = Renderer2D::GetStats();
//        ImGui::Text("Renderer2D Stats:");
//        ImGui::Text("Draw Calls: %d", stats.DrawCalls);
//        ImGui::Text("Quads: %d", stats.QuadCount);
//        ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
//        ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

        ImGui::End();

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
        ImGui::Begin("Viewport");
        auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
        auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
        auto viewportOffset = ImGui::GetWindowPos();
        m_ViewportBounds[0] = { viewportMinRegion.x + viewportOffset.x, viewportMinRegion.y + viewportOffset.y };
        m_ViewportBounds[1] = { viewportMaxRegion.x + viewportOffset.x, viewportMaxRegion.y + viewportOffset.y };

        m_ViewportFocused = ImGui::IsWindowFocused();
        m_ViewportHovered = ImGui::IsWindowHovered();
//        Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused && !m_ViewportHovered);

        ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
        m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };

        uint32_t textureID = m_Framebuffer->GetColorAttachment();
        ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

//        if (ImGui::BeginDragDropTarget())
//        {
//            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM"))
//            {
//                const wchar_t* path = (const wchar_t*)payload->Data;
//                OpenScene(std::filesystem::path(g_AssetPath) / path);
//            }
//            ImGui::EndDragDropTarget();
//        }

        ImGui::End();
        ImGui::PopStyleVar();

//        UI_Toolbar();

        ImGui::End();
    }
}
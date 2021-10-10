#include "UILayer.h"

#include "Events/EditorEvents.h"
#include "Core/FileDialog.h"

#include <Engine/Core/Events/EventPublisher.h>
#include <Engine/Core/Rendering/RenderCommand.h>
#include <Engine/Core/Rendering/Renderer.h>
#include <Engine/Project/Entities/Components.h>

#include <imgui.h>
#include <imgui_internal.h>

namespace Shell::Editor {
    static ImGuiTreeNodeFlags BASE_NODE_FLAGS = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;

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
                {
                    auto outPath = FileDialog::PickFolder();
                    SHELL_INFO("Chosen path: {0}", outPath.generic_string().c_str());
                }

                if (ImGui::MenuItem("Exit")) {}

                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }

        ImGui::Begin("Stats");

        std::string name = "None";
        if (m_SelectedEntity)
            name = m_SelectedEntity->GetName();
        ImGui::Text("Hovered Entity: %s", name.c_str());

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

        ImGui::End();
        ImGui::PopStyleVar();

        ImGui::Begin("Entities");

        if (ImGui::IsWindowFocused(ImGuiFocusedFlags_ChildWindows) && ImGui::IsMouseClicked(ImGuiPopupFlags_MouseButtonRight)) {
            ImGui::OpenPopup("entity context");
        }

        if (ImGui::BeginPopupContextWindow("entity context"))
        {
            if (ImGui::BeginMenu("Create Entity")) {
                if (ImGui::MenuItem("Empty", NULL, false)) {
                    auto eventEntity = m_EntityManager->CreateEntity(m_CurrentSceneBluePrint, "Entity");
                    CreateEntityEvent event(eventEntity, m_SelectedEntity);

                    EventPublisher::Instance()->Publish(event);
                    ImGui::CloseCurrentPopup();
                }
                else if (ImGui::MenuItem("Sprite", NULL, false)) {
                    ImGui::CloseCurrentPopup();
                }
                ImGui::EndMenu();
            }
            ImGui::EndPopup();
        }

        for (SceneEntity * entity: m_CurrentSceneBluePrint->GetEntityTree()) {
            RenderTree(entity);
        }

        ImGui::End();

        ImGui::End();
    }

    void EditorUILayer::OnEvent(Event &event) {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<CreateEntityEvent>(SHELL_BIND_EVENT_FN(EditorUILayer::OnCreateEntityEvent));
    }

    ImRect EditorUILayer::RenderTree(SceneEntity *entity) {
        ImGuiTreeNodeFlags nodeFlags = BASE_NODE_FLAGS;

        if (m_SelectedEntity == entity) {
            nodeFlags |= ImGuiTreeNodeFlags_Selected;
        }

        const bool recurse = ImGui::TreeNodeEx(entity->GetName().c_str(), nodeFlags);
        if (ImGui::IsItemClicked(ImGuiPopupFlags_MouseButtonLeft) || ImGui::IsItemClicked(ImGuiPopupFlags_MouseButtonRight)) {

            if (m_SelectedEntity == entity) {
                m_SelectedEntity = nullptr;
            } else {
                m_SelectedEntity = entity;
            }
        }

        ImGui::OpenPopupOnItemClick("entity context", ImGuiPopupFlags_MouseButtonRight);

        const ImRect nodeRect = ImRect(ImGui::GetItemRectMin(), ImGui::GetItemRectMax());

        if (recurse)
        {
            const ImColor TreeLineColor = ImGui::GetColorU32(ImGuiCol_Text);
            const float SmallOffsetX = 0.0f; //for now, a hardcoded value; should take into account tree indent size
            ImDrawList* drawList = ImGui::GetWindowDrawList();

            ImVec2 verticalLineStart = ImGui::GetCursorScreenPos();
            verticalLineStart.x += SmallOffsetX; //to nicely line up with the arrow symbol
            ImVec2 verticalLineEnd = verticalLineStart;

            for (SceneEntity * child : entity->GetChildren())
            {
                const float HorizontalTreeLineSize = 8.0f; //chosen arbitrarily
                const ImRect childRect = RenderTree(child);
                const float midpoint = (childRect.Min.y + childRect.Max.y) / 2.0f;
                drawList->AddLine(ImVec2(verticalLineStart.x, midpoint), ImVec2(verticalLineStart.x + HorizontalTreeLineSize, midpoint), TreeLineColor);
                verticalLineEnd.y = midpoint;
            }

            drawList->AddLine(verticalLineStart, verticalLineEnd, TreeLineColor);
            ImGui::TreePop();
        }

        return nodeRect;
    }

    bool EditorUILayer::OnCreateEntityEvent(CreateEntityEvent &event) {

        auto entity = event.GetEntity();
        auto parentEntity = event.GetParentEntity();

        m_CurrentSceneBluePrint->GetEntities().push_back(entity);

        if (parentEntity == nullptr) {
            m_CurrentSceneBluePrint->GetEntityTree().push_back(entity);
        } else {
            parentEntity->AddChild(entity);
        }

        return false;
    }
}
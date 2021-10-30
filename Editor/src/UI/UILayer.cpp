#include "UILayer.h"

#include "Core/FileDialog.h"
#include "Project/ProjectSerializer.h"
#include "Project/SceneSerializer.h"
#include "UI/Panel/EntityPropsPanel.h"

#include <Engine/Core/Application.h>
#include <Engine/Core/Events/EventPublisher.h>
#include <Engine/Core/Rendering/RenderCommand.h>
#include <Engine/Core/Rendering/Renderer.h>
#include <Engine/Project/Entities/Components.h>
#include <Engine/Runtime/RuntimeManager.h>
#include <Engine/Scripting/VisualStudioProjectManager.h>

#include <imgui.h>
#include <imgui_internal.h>

namespace Shell::Editor {
    static ImGuiTreeNodeFlags BASE_NODE_FLAGS = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;

    EditorUILayer::EditorUILayer()
    : Layer("UI Layer"),
      m_ClearColor(glm::vec4(0.2f, 0.2f, 0.2f, 1)),
      m_Camera(new Shell::OrthographicCamera(-1.6f, 1.6f, -0.9f, 0.9f)),
      m_Panels({
          new EntityPropsPanel
      })
    {
    }

    EditorUILayer::~EditorUILayer() {
        for (const auto &panel: m_Panels) {
            delete panel;
        }
    }

    void EditorUILayer::OnAttach() {
        for (const auto &panel: m_Panels) {
            panel->SetState(&m_UiState);
        }

        FrameBufferSpecification frameBufferSpec;
        frameBufferSpec.Width = 1280;
        frameBufferSpec.Height = 720;

        m_Framebuffer = FrameBuffer::Create(frameBufferSpec);
        m_RenderQueue = CreateRef<RenderQueue>();
        m_RenderQueue->Init();

        m_UiState.CurrentSceneBluePrint = CreateRef<SceneBlueprint>("Initial-Scene");

        Shell::RenderCommand::Create()->SetViewport(frameBufferSpec.Width, frameBufferSpec.Height);
    }

    void EditorUILayer::OnUpdate(std::chrono::milliseconds deltaTime) {

        // Check for resizing
        auto spec = m_Framebuffer->GetSpecification();
        if (m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f && // zero sized framebuffer is invalid
            (spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y)) {
            m_Framebuffer->Resize(m_ViewportSize.x, m_ViewportSize.y);

            m_Camera->SetViewportSize(m_ViewportSize.x, m_ViewportSize.y);
        }

        m_Framebuffer->Bind();

        Shell::Runtime::RuntimeManager::Instance()->RunLifecycleMethod(m_UiState.CurrentSceneBluePrint, "OnUpdate");

        Shell::RenderCommand::Create()->SetClearColor(m_ClearColor);
        Shell::RenderCommand::Create()->Clear();

        Shell::Renderer::Instance()->BeginScene(m_Camera);

        m_RenderQueue->StartBatch();

        auto view = EntityManager::Instance()->GetComponentView<TransformComponent, SpriteComponent>();
        for(auto &&[entity, transform, sprite] : view.each()) {
            if (sprite.Texture) {
                m_RenderQueue->EnqueueTexturedQuad(sprite.Texture, transform.GetTransform());
            } else {
                // assume that it needs a color
                m_RenderQueue->EnqueueColoredQuad(sprite.Color, transform.GetTransform());
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
//        ImGui::ShowDemoWindow(&dockspaceOpen);

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

        RenderMenu();

        for (const auto &panel: m_Panels) {
            panel->Render();
        }

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
                    auto eventEntity = EntityManager::Instance()->CreateEntity(m_UiState.CurrentSceneBluePrint, "Entity");
                    CreateEntityEvent event(eventEntity, m_UiState.SelectedEntity);

                    EventPublisher::Instance()->Publish(event);
                    ImGui::CloseCurrentPopup();
                }
                else if (ImGui::MenuItem("Sprite", NULL, false)) {
                    auto eventEntity = EntityManager::Instance()->CreateEntity(m_UiState.CurrentSceneBluePrint, "Entity");
                    EntityManager::Instance()->AddComponent<SpriteComponent>(eventEntity, glm::vec4(1.0f, 0.f, 0.0f, 1.0f));

                    CreateEntityEvent event(eventEntity, m_UiState.SelectedEntity);

                    EventPublisher::Instance()->Publish(event);
                    ImGui::CloseCurrentPopup();
                }
                ImGui::EndMenu();
            }
            ImGui::EndPopup();
        }

        for (SceneEntity * entity: m_UiState.CurrentSceneBluePrint->GetEntityTree()) {
            RenderTree(entity);
        }

        ImGui::End();

        ImGui::End();
    }

    void EditorUILayer::OnEvent(Event &event) {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<CreateEntityEvent>(SHELL_BIND_EVENT_FN(EditorUILayer::OnCreateEntityEvent));
        dispatcher.Dispatch<SaveProjectEvent>(SHELL_BIND_EVENT_FN(EditorUILayer::OnSaveProjectEvent));
        dispatcher.Dispatch<LoadProjectEvent>(SHELL_BIND_EVENT_FN(EditorUILayer::OnLoadProjectEvent));
        dispatcher.Dispatch<SaveSceneEvent>(SHELL_BIND_EVENT_FN(EditorUILayer::OnSaveSceneEvent));
        dispatcher.Dispatch<LoadSceneEvent>(SHELL_BIND_EVENT_FN(EditorUILayer::OnLoadSceneEvent));
    }

    void EditorUILayer::RenderMenu() {
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("Project"))
            {
                if (ImGui::MenuItem("New", "Ctrl+N"))
                {
                    auto outPath = FileDialog::PickFolder();

                    if (!outPath.empty()) {
                        if (m_UiState.Project == nullptr) {
                            m_UiState.Project = new Project(L"Sample game", outPath);
                        }

                        SaveProjectEvent event(m_UiState.Project);
                        EventPublisher::Instance()->Publish(event);
                    }
                }

                if (ImGui::MenuItem("Open...", "Ctrl+O"))
                {
                    auto outPath = FileDialog::PickFolder();

                    if (!outPath.empty()) {
                        LoadProjectEvent event(outPath);
                        EventPublisher::Instance()->Publish(event);
                    }
                }

                if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S"))
                {
                    auto outPath = FileDialog::PickFolder();

                    if (!outPath.empty()) {
                        if (m_UiState.Project == nullptr) {
                            m_UiState.Project = new Project(L"Sample game", outPath);
                        }

                        SaveProjectEvent event(m_UiState.Project);
                        EventPublisher::Instance()->Publish(event);
                    }
                }

                if (ImGui::MenuItem("Exit")) {}

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Scenes"))
            {

                if (ImGui::MenuItem("New"))
                {
                    auto outPath = FileDialog::SaveFile();

                    if (!outPath.empty()) {
                        SaveSceneEvent event(m_UiState.CurrentSceneBluePrint, outPath);
                        EventPublisher::Instance()->Publish(event);
                    }
                }

                if (ImGui::MenuItem("Open"))
                {
                    auto outPath = FileDialog::ChooseFile();

                    if (!outPath.empty()) {
                        LoadSceneEvent event(outPath);
                        EventPublisher::Instance()->Publish(event);
                    }
                }

                if (ImGui::MenuItem("Save As..."))
                {
                    auto outPath = FileDialog::SaveFile();

                    if (!outPath.empty()) {
                        SaveSceneEvent event(m_UiState.CurrentSceneBluePrint, outPath);
                        EventPublisher::Instance()->Publish(event);
                    }
                }

                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }
    }

    ImRect EditorUILayer::RenderTree(SceneEntity *entity) {
        ImGuiTreeNodeFlags nodeFlags = BASE_NODE_FLAGS;

        if (m_UiState.SelectedEntity == entity) {
            nodeFlags |= ImGuiTreeNodeFlags_Selected;
        }

        const bool recurse = ImGui::TreeNodeEx(entity->GetName().c_str(), nodeFlags);
        if (ImGui::IsItemClicked(ImGuiPopupFlags_MouseButtonLeft) || ImGui::IsItemClicked(ImGuiPopupFlags_MouseButtonRight)) {

            if (m_UiState.SelectedEntity == entity) {
                m_UiState.SelectedEntity = nullptr;
                m_UiState.ChangedEntity = false;
            } else {

                // make sure fields are not overwritten when changing from one selection to the other
                if (m_UiState.SelectedEntity != nullptr) {
                    m_UiState.ChangedEntity = true;
                } else {
                    m_UiState.ChangedEntity = false;
                }

                m_UiState.SelectedEntity = entity;
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

        m_UiState.CurrentSceneBluePrint->GetEntities().push_back(entity);

        if (parentEntity == nullptr) {
            m_UiState.CurrentSceneBluePrint->GetEntityTree().push_back(entity);
        } else {
            parentEntity->AddChild(entity);
        }

        return true;
    }

    bool EditorUILayer::OnSaveProjectEvent(SaveProjectEvent &event) {

        auto project = event.GetProject();
        auto projectPath = project->GetPath();
        if (!std::filesystem::exists(projectPath)) {
            std::filesystem::create_directories(projectPath);
        }

        auto vsManager = new Scripting::VisualStudioProjectManager;
        vsManager->CreateProject(projectPath, project->GetNameAsSimpleString());

        project->GetSettings()->SetAppLibraryPath("bin/Debug/Custom-App.dll");

        ProjectSerializer::SerializeToFile(project);
        Application::Instance()->GetWindow()->SetTitle(fmt::format("Project - {0}", m_UiState.Project->GetNameAsSimpleString()));

        return true;
    }

    bool EditorUILayer::OnLoadProjectEvent(LoadProjectEvent &event) {
        auto project = ProjectSerializer::DeserializeFromFile(event.GetProjectPath());

        if (project == nullptr) {
            return false;
        }

        m_UiState.Project = project;

        Application::Instance()->GetWindow()->SetTitle(fmt::format("Project - {0}", m_UiState.Project->GetNameAsSimpleString()));
        auto appPath = project->GetPath() / project->GetSettings()->GetAppLibraryPath();
        Runtime::RuntimeManager::Instance()->LoadAppLibrary(appPath.string());

        return true;
    }

    bool EditorUILayer::OnSaveSceneEvent(SaveSceneEvent &event) {
        SceneSerializer::SerializeToFile(event.GetPath(), event.GetBlueprint());

        return true;
    }

    bool EditorUILayer::OnLoadSceneEvent(LoadSceneEvent & event) {
        m_UiState.CurrentSceneBluePrint = SceneSerializer::DeserializeFromFile(event.GetScenePath());
        Runtime::RuntimeManager::Instance()->InstantiateScene(m_UiState.CurrentSceneBluePrint);

        return true;
    }
}
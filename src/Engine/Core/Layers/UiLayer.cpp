#include "UiLayer.h"

#include "Engine/Core/Application.h"
#include "Engine/UI/imgui_impl_glfw.h"
#include "Engine/UI/imgui_impl_opengl3.h"

#include <imgui.h>
#include <GLFW/glfw3.h>

namespace Shell {
    UiLayer::UiLayer() : Layer("UI Layer") {
    }

    void UiLayer::OnAttach() {
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
        io.BackendFlags |= ImGuiBackendFlags_HasGamepad;

        Application * app = Application::Instance();
        io.DisplaySize = ImVec2((float)app->GetWindow()->GetWidth(), (float)app->GetWindow()->GetHeight());

        // Setup Platform/Renderer bindings
        ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow *>(app->GetWindow()->GetNativeWindow()), true);
        ImGui_ImplOpenGL3_Init("#version 410");
        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
    }

    void UiLayer::OnDetach() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void UiLayer::OnUpdate() {
        // feed inputs to dear imgui, start new frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGuiIO &io = ImGui::GetIO();
        auto time = (float) glfwGetTime();
        io.DeltaTime = m_Time > 0.0 ? (time - m_Time) : (1.0f / 60.0f);
        m_Time = time;

        // render your GUI
        ImGui::Begin("Demo window");
        ImGui::Button("Hello!");
        ImGui::End();

        // Render dear imgui into screen
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void UiLayer::OnEvent(Event &event) {
        Layer::OnEvent(event);
    }
}

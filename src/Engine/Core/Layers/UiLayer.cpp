#include "UiLayer.h"

#include "Engine/Core/Application.h"
#include "Engine/Core/Profiling.h"
#include "Engine/UI/imgui_impl_glfw.h"
#include "Engine/UI/imgui_impl_opengl3.h"

#include <imgui.h>
#include <GLFW/glfw3.h>

namespace Shell {
    UiLayer::UiLayer() : Layer("UI Layer") {
    }

    void UiLayer::OnAttach() {
        OPTICK_EVENT();

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
        io.BackendFlags |= ImGuiBackendFlags_HasGamepad;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

        Application * app = Application::Instance();
        io.DisplaySize = ImVec2((float)app->GetWindow()->GetWidth(), (float)app->GetWindow()->GetHeight());

        // Setup Platform/Renderer bindings
        ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow *>(app->GetWindow()->GetNativeWindow()), true);
        ImGui_ImplOpenGL3_Init("#version 410");
        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
    }

    void UiLayer::OnDetach() {
        OPTICK_EVENT();

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void UiLayer::OnUiRender() {
    }

    void UiLayer::Begin() {
        OPTICK_EVENT();

        // feed inputs to dear imgui, start new frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void UiLayer::End() {
        OPTICK_EVENT();

        ImGuiIO &io = ImGui::GetIO();
        auto app = Application::Instance();
        io.DisplaySize = ImVec2((float) app->GetWindow()->GetWidth(), (float) app->GetWindow()->GetHeight());

        // Render dear imgui into screen
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow* backupCurrentContext = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backupCurrentContext);
        }
    }
}

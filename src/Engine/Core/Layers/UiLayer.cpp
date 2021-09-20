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
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<MouseButtonPressedEvent>(SHELL_BIND_EVENT_FN(UiLayer::OnMouseButtonPressedEvent));
        dispatcher.Dispatch<MouseButtonReleasedEvent>(SHELL_BIND_EVENT_FN(UiLayer::OnMouseButtonReleasedEvent));
        dispatcher.Dispatch<MouseMovedEvent>(SHELL_BIND_EVENT_FN(UiLayer::OnMouseMovedEvent));
        dispatcher.Dispatch<MouseScrolledEvent>(SHELL_BIND_EVENT_FN(UiLayer::OnMouseScrolledEvent));
        dispatcher.Dispatch<KeyPressedEvent>(SHELL_BIND_EVENT_FN(UiLayer::OnKeyPressedEvent));
        dispatcher.Dispatch<KeyReleasedEvent>(SHELL_BIND_EVENT_FN(UiLayer::OnKeyReleasedEvent));
        dispatcher.Dispatch<WindowResizeEvent>(SHELL_BIND_EVENT_FN(UiLayer::OnWindowResizeEvent));
    }

    bool UiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent &event) {
        ImGuiIO &io = ImGui::GetIO();
        io.MouseDown[event.GetMouseButton()] = true;

        return false;
    }

    bool UiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent &event) {
        ImGuiIO &io = ImGui::GetIO();
        io.MouseDown[event.GetMouseButton()] = false;

        return false;
    }

    bool UiLayer::OnMouseMovedEvent(MouseMovedEvent &event) {
        ImGuiIO &io = ImGui::GetIO();
        io.MousePos = ImVec2(event.GetX(), event.GetY());

        return false;
    }

    bool UiLayer::OnMouseScrolledEvent(MouseScrolledEvent &event) {
        ImGuiIO &io = ImGui::GetIO();
        io.MouseWheelH += event.GetXOffset();
        io.MouseWheel += event.GetYOffset();

        return false;
    }

    bool UiLayer::OnKeyPressedEvent(KeyPressedEvent &event) {
        ImGuiIO &io = ImGui::GetIO();
        io.KeysDown[event.GetKeyCode()] = true;

        // Modifiers are not reliable across systems
        io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
        io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
        io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
        io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

        return false;
    }

    bool UiLayer::OnKeyReleasedEvent(KeyReleasedEvent &event) {
        ImGuiIO &io = ImGui::GetIO();
        io.KeysDown[event.GetKeyCode()] = false;

        return false;
    }

    bool UiLayer::OnWindowResizeEvent(WindowResizeEvent &event) {
        ImGuiIO &io = ImGui::GetIO();

        auto w = (float) event.GetWidth();
        auto h = (float) event.GetHeight();

        io.DisplaySize = ImVec2(w, h);

        return false;
    }
}

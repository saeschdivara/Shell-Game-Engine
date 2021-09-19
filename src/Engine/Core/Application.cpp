#include "Engine/Core/Application.h"
#include "Engine/Core/Logger.h"
#include "Engine/Core/Base.h"
#include "Engine/Core/Layers/UiLayer.h"

namespace Shell {
    Application* Application::m_Instance = nullptr;

    Application::Application() {
        m_Instance = this;
    }

    Application *Application::Instance() {
        return m_Instance;
    }

    void Application::Init() {
        Logger::Init();

        m_Window = new Window;
        m_Window->Init();

        m_Window->SetupCallbacks(SHELL_BIND_EVENT_FN(Application::OnEvent));

        PushOverlay(new UiLayer);
    }

    void Application::Run() {

        while (m_IsRunning) {
            for (Layer* layer : m_LayerStack) {
                layer->OnUpdate();
            }

            m_Window->OnUpdate();
        }
    }

    void Application::OnEvent(Event &event) {

        SHELL_CORE_INFO(event.ToString());

        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowCloseEvent>(SHELL_BIND_EVENT_FN(Application::OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(SHELL_BIND_EVENT_FN(Application::OnWindowResize));

        for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
        {
            if (event.Handled)
                break;
            (*it)->OnEvent(event);
        }
    }

    void Application::PushLayer(Layer *layer) {
        m_LayerStack.PushLayer(layer);
    }

    void Application::PushOverlay(Layer *overlay) {
        m_LayerStack.PushOverlay(overlay);
    }

    bool Application::OnWindowClose(WindowCloseEvent &e) {
        m_IsRunning = false;
        return true;
    }

    bool Application::OnWindowResize(WindowResizeEvent &e) {
        return true;
    }
}

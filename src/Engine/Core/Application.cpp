#include "Engine/Core/Application.h"
#include "Engine/Core/Rendering/RenderCommand.h"

#include "Engine/Core/Profiling.h"

namespace Shell {
    Application* Application::m_Instance = nullptr;

    Application::Application() {
        m_Instance = this;
    }

    Application::~Application() {
        OPTICK_STOP_CAPTURE();
        OPTICK_SAVE_CAPTURE("./profiling");
    }

    Application *Application::Instance() {
        return m_Instance;
    }

    void Application::Init() {
        OPTICK_START_CAPTURE();
        OPTICK_EVENT();

        Logger::Init();

        m_Window = CreateScope<Window>();
        m_Window->Init();

        m_Window->SetupCallbacks(SHELL_BIND_EVENT_FN(Application::OnEvent));

        m_UiLayer = new UiLayer;
        PushOverlay(m_UiLayer);

        m_Runtime = Runtime::RuntimeManager::Instance();
        m_Runtime->Init();
        m_Runtime->LoadEngineLibrary();
    }

    void Application::Run() {

        while (m_IsRunning) {
            OPTICK_FRAME("MainThread");

            auto currentTime = std::chrono::high_resolution_clock::now();
            auto timeStep = currentTime - m_LastFrameTime;
            m_LastFrameTime = currentTime;

            for (Layer* layer : m_LayerStack) {
                layer->OnUpdate(std::chrono::duration_cast<std::chrono::milliseconds>(timeStep));
            }

            m_UiLayer->Begin();
            for (Layer* layer : m_LayerStack) {
                layer->OnUiRender();
            }
            m_UiLayer->End();

            m_Window->OnUpdate();
        }
    }

    void Application::OnEvent(Event &event) {
        OPTICK_EVENT();

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
        OPTICK_EVENT();
        m_LayerStack.PushLayer(layer);
    }

    void Application::PushOverlay(Layer *overlay) {
        OPTICK_EVENT();
        m_LayerStack.PushOverlay(overlay);
    }

    bool Application::OnWindowClose(WindowCloseEvent &e) {
        OPTICK_EVENT();
        m_IsRunning = false;
        return true;
    }

    bool Application::OnWindowResize(WindowResizeEvent &e) {
        OPTICK_EVENT();
        RenderCommand::Create()->SetViewport(e.GetWidth(), e.GetHeight());
        return true;
    }
}

#include "Engine/Core/shellpch.h"
#include "Engine/Core/Application.h"
#include "Engine/Core/Rendering/Renderer.h"
#include "Engine/Core/Rendering/RenderCommand.h"

namespace Shell {
    Application* Application::m_Instance = nullptr;

    Application::Application() {
        m_Instance = this;
    }

    Application::~Application() {
    }

    Application *Application::Instance() {
        return m_Instance;
    }

    void Application::Init() {
        Logger::Init();

        m_Window = CreateScope<Window>();
        m_Window->Init();

        m_Window->SetupCallbacks(SHELL_BIND_EVENT_FN(Application::OnEvent));

        m_UiLayer = new UiLayer;
        PushOverlay(m_UiLayer);

        m_BufferContainer = BufferContainer::Create();

        float vertices [] = {
                -0.5f, -0.5f, 0.0f, 0.3f, 0.3f, 1.0f, 1.0f,
                 0.5f, -0.5f, 0.0f, 0.3f, 0.7f, 0.2f, 1.0f,
                 0.0f,  0.5f, 0.0f, 1.0f, 0.3f, 1.0f, 1.0f
        };

        auto m_VertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));

        BufferLayout layout = {
            { ShaderDataType::Float3, "a_Position" },
            { ShaderDataType::Float4, "a_Color" },
        };

        m_VertexBuffer->SetLayout(layout);
        m_BufferContainer->AddBuffer(m_VertexBuffer);

        uint32_t indices[3] = { 0, 1, 2 };
        auto m_IndexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
        m_BufferContainer->AddBuffer(m_IndexBuffer);

        std::string vertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;

            out vec4 v_Color;

            void main()
            {
                v_Color = a_Color;
                gl_Position = vec4(a_Position, 1.0);
            }
        )";

        std::string fragmentSrc = R"(
            #version 330 core
            layout(location = 0) out vec4 color;

            in vec4 v_Color;

            void main()
            {
                color = v_Color;
            }
        )";

        m_Shader = CreateScope<Shader>(vertexSrc, fragmentSrc);
    }

    void Application::Run() {

        auto clearColor = glm::vec4(0.2f, 0.2f, 0.2f, 1);

        while (m_IsRunning) {

            RenderCommand::Create()->SetClearColor(clearColor);
            RenderCommand::Create()->Clear();

            Renderer::Instance()->BeginScene();

            m_Shader->Bind();
            Renderer::Instance()->Submit(m_BufferContainer);

            Renderer::Instance()->EndScene();

            for (Layer* layer : m_LayerStack) {
                layer->OnUpdate();
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

        SHELL_CORE_DEBUG(event.ToString());

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

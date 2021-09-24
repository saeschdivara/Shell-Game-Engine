#include "Engine/Core/shellpch.h"
#include "Engine/Core/Application.h"
#include "Engine/Core/Layers/UiLayer.h"

#include <glad/glad.h>

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

        glGenVertexArrays(1, &m_VertexArray);
        glBindVertexArray(m_VertexArray);

        float vertices [3 * 3] = {
                -0.5f, -0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
                0.0f,  0.5f, 0.0f
        };

        m_VertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

        uint32_t indices[3] = { 0, 1, 2 };
        m_IndexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

        std::string vertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;

            void main()
            {
                gl_Position = vec4(a_Position, 1.0);
            }
        )";

        std::string fragmentSrc = R"(
            #version 330 core
            layout(location = 0) out vec4 color;

            void main()
            {
                color = vec4(0.4, 0.3, 0.2, 1.0);
            }
        )";

        m_Shader = CreateScope<Shader>(vertexSrc, fragmentSrc);
    }

    void Application::Run() {

        while (m_IsRunning) {

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the buffers

            m_Shader->Bind();
            glBindVertexArray(m_VertexArray);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

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

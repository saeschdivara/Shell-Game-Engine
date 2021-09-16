#include "Engine/Core/Application.h"
#include "Engine/Core/Logger.h"
#include "Engine/Core/Base.h"

namespace Shell {

    void Application::Init() {
        Logger::Init();

        m_Window = new Window;
        m_Window->Init();

        m_Window->SetupCallbacks(SHELL_BIND_EVENT_FN(Application::OnEvent));
    }

    void Application::OnEvent(Event &event) {

        SHELL_CORE_INFO(event.ToString());

        for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
        {
            if (event.Handled)
                break;
            (*it)->OnEvent(event);
        }
    }
}

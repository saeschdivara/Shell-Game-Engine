#include "Application.h"
#include "Engine/Core/Logger.h"

namespace Shell {

    void Application::Init() {
        Logger::Init();

        m_window = new Window;
        m_window->Init();
    }
}

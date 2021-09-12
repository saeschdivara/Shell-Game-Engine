#pragma once

#include "Window.h"

namespace Shell {

    class Application {
    public:
        virtual ~Application() {
            delete m_window;
        }

        virtual void Init();
        virtual void Run() = 0;

    protected:
        Window* m_window = nullptr;
    };
}



#pragma once

#include "Engine/Core/Utils.h"
#include "Engine/Core/Window.h"
#include "Engine/Core/Events/Event.h"
#include "Engine/Core/Layers/LayerStack.h"

namespace Shell {

    class Application {
    public:
        virtual ~Application() {
            delete m_Window;
        }

        virtual void Init();
        virtual void Run() = 0;

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);

        virtual void OnEvent(Event & event);

    protected:
        Window* m_Window = nullptr;
        LayerStack m_LayerStack;
    };
}



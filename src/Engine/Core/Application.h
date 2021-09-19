#pragma once

#include "Engine/Core/Utils.h"
#include "Engine/Core/Window.h"
#include "Engine/Core/Events/ApplicationEvent.h"
#include "Engine/Core/Events/Event.h"
#include "Engine/Core/Layers/LayerStack.h"

namespace Shell {

    class Application {
    public:
        Application();

        virtual ~Application() {
            delete m_Window;
        }

        static Application* Instance();

        virtual void Init();
        virtual void Run();

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);

        virtual void OnEvent(Event & event);

        inline Window* GetWindow() { return m_Window; }

    protected:
        Window* m_Window = nullptr;
        LayerStack m_LayerStack;

        bool m_IsRunning = true;

    private:
        static Application* m_Instance;

        bool OnWindowClose(WindowCloseEvent& e);
        bool OnWindowResize(WindowResizeEvent& e);
    };
}



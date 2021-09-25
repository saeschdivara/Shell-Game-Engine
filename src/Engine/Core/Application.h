#pragma once

#include "Engine/Core/Utils.h"
#include "Engine/Core/Window.h"
#include "Engine/Core/Events/ApplicationEvent.h"
#include "Engine/Core/Events/Event.h"
#include "Engine/Core/Layers/LayerStack.h"
#include "Engine/Core/Layers/UiLayer.h"

#include "Engine/Core/Rendering/Shader.h"
#include "Engine/Core/Rendering/Buffer.h"
#include "Engine/Core/Rendering/BufferContainer.h"

namespace Shell {

    class Application {
    public:
        Application();
        virtual ~Application();

        static Application* Instance();

        virtual void Init();
        virtual void Run();

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);

        virtual void OnEvent(Event & event);

        inline Window* GetWindow() { return m_Window.get(); }

    protected:
        Scope<Window> m_Window = nullptr;
        LayerStack m_LayerStack;
        UiLayer * m_UiLayer;

        bool m_IsRunning = true;

    private:
        static Application* m_Instance;

        bool OnWindowClose(WindowCloseEvent& e);
        bool OnWindowResize(WindowResizeEvent& e);
    };
}



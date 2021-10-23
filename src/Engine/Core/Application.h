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

#include "Engine/Runtime/RuntimeManager.h"

#include <chrono>

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
        Ref<Runtime::RuntimeManager> m_Runtime;
        LayerStack m_LayerStack;
        UiLayer * m_UiLayer;

        bool m_IsRunning = true;

        std::chrono::high_resolution_clock::time_point m_LastFrameTime;

    private:
        static Application* m_Instance;

        bool OnWindowClose(WindowCloseEvent& e);
        bool OnWindowResize(WindowResizeEvent& e);
    };
}



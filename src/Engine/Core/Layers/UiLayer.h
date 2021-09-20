#pragma once

#include "Engine/Core/Layers/Layer.h"
#include "Engine/Core/Events/ApplicationEvent.h"
#include "Engine/Core/Events/KeyEvent.h"
#include "Engine/Core/Events/MouseEvent.h"

namespace Shell {
    class UiLayer : public Layer {
    public:
        UiLayer();

        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate() override;

        void OnEvent(Event &event) override;

    private:
        bool OnMouseButtonPressedEvent(MouseButtonPressedEvent &event);
        bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent &event);
        bool OnMouseMovedEvent(MouseMovedEvent &event);
        bool OnMouseScrolledEvent(MouseScrolledEvent &event);
        bool OnKeyPressedEvent(KeyPressedEvent &event);
        bool OnKeyReleasedEvent(KeyReleasedEvent &event);
        bool OnWindowResizeEvent(WindowResizeEvent &event);

    private:
        float m_Time = 0.0f;
    };
}



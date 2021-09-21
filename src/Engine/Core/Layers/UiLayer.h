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

        void OnUiRender() override;

        virtual void Begin();
        virtual void End();
    };
}



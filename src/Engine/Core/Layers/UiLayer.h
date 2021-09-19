#pragma once

#include "Engine/Core/Layers/Layer.h"

namespace Shell {
    class UiLayer : public Layer {
    public:
        UiLayer();

        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate() override;

        void OnEvent(Event &event) override;

    private:
        float m_Time = 0.0f;
    };
}



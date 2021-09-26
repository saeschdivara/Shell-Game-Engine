#pragma once

#include "Engine/Core/Events/Event.h"
#include "Engine/Core/shellpch.h"

namespace Shell {

    class Layer {
    public:
        Layer(const std::string & name);
        virtual ~Layer();

        virtual void OnAttach() {};
        virtual void OnDetach() {};
        virtual void OnUpdate(std::chrono::milliseconds deltaTime) {};
        virtual void OnUiRender() {};
        virtual void OnEvent(Event & event) {};

    protected:
        std::string m_Name;
    };
}



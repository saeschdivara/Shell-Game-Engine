#pragma once

#include "Engine/Core/shellpch.h"
#include "Engine/Core/Events/Event.h"

namespace Shell {

    class EventPublisher {
    public:
        static Ref<EventPublisher> Instance();

        void Publish(Event & event);

    private:
        EventPublisher() = default;

        static  Ref<EventPublisher> m_Instance;
    };

}


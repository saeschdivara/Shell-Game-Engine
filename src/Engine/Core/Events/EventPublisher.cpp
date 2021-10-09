#include "EventPublisher.h"

#include "Engine/Core/Application.h"

namespace Shell {
    Ref<EventPublisher> EventPublisher::m_Instance = nullptr;

    Ref<EventPublisher> EventPublisher::Instance() {

        if (!m_Instance) {
            m_Instance.reset(new EventPublisher);
        }

        return m_Instance;
    }

    void EventPublisher::Publish(Event &event) {
        Application::Instance()->OnEvent(event);
    }
}
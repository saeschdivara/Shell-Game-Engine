#pragma once

#include <Engine/Core/Events/Event.h>
#include <Engine/Project/Entities/SceneEntity.h>

namespace Shell::Editor {
    class EntityEvent : public Event
    {
    public:
        [[nodiscard]] SceneEntity * GetEntity() const { return m_Entity; }

        EVENT_CLASS_TYPE(AppCustomEvent)
        EVENT_CLASS_CATEGORY(EventCategoryCustom)

    protected:
        EntityEvent(SceneEntity * entity) : m_Entity(entity) {}

        SceneEntity * m_Entity;
    };

    class CreateEntityEvent : public EntityEvent
    {
    public:
        CreateEntityEvent(SceneEntity * entity, SceneEntity * parentEntity)
        : EntityEvent(entity), m_ParentEntity(parentEntity)
        {}

        [[nodiscard]] SceneEntity * GetParentEntity() const { return m_ParentEntity; }

    private:
        SceneEntity * m_ParentEntity;
    };
}
#pragma once

#include <Engine/Core/Events/Event.h>
#include <Engine/Project/Project.h>
#include <Engine/Project/Entities/SceneEntity.h>

namespace Shell::Editor {
    class EditorEvent : public Event
    {
    public:
        EVENT_CLASS_TYPE(AppCustomEvent)
        EVENT_CLASS_CATEGORY(EventCategoryCustom)

    protected:
        EditorEvent() = default;
    };

    class EntityEvent : public EditorEvent
    {
    public:
        [[nodiscard]] SceneEntity * GetEntity() const { return m_Entity; }

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

    class SaveProjectEvent : public EditorEvent
    {
    public:
        SaveProjectEvent(Project * project) : m_Project(project) {}

        [[nodiscard]] Project *getProject() const {
            return m_Project;
        }

    private:
        Project * m_Project;
    };
}
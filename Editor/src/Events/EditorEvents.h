#pragma once

#include <Engine/Core/shellpch.h>
#include <Engine/Core/Events/Event.h>
#include <Engine/Project/Project.h>
#include <Engine/Project/SceneBlueprint.h>
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

        [[nodiscard]] Project *GetProject() const {
            return m_Project;
        }

    private:
        Project * m_Project;
    };

    class LoadProjectEvent : public EditorEvent
    {
    public:
        LoadProjectEvent(std::filesystem::path projectPath) : m_ProjectPath(std::move(projectPath)) {}

        const std::filesystem::path &GetProjectPath() const {
            return m_ProjectPath;
        }

    private:
        std::filesystem::path m_ProjectPath;
    };

    class SaveSceneEvent : public EditorEvent
    {
    public:
        SaveSceneEvent(Ref<SceneBlueprint> bluePrint, std::filesystem::path path)
        : m_SceneBlueprint(bluePrint), m_Path(path) {}

        [[nodiscard]] Ref<SceneBlueprint> GetBlueprint() const {
            return m_SceneBlueprint;
        }

        const std::filesystem::path &GetPath() const {
            return m_Path;
        }

    private:
        Ref<SceneBlueprint> m_SceneBlueprint;
        std::filesystem::path m_Path;
    };

    class LoadSceneEvent : public EditorEvent
    {
    public:
        LoadSceneEvent(std::filesystem::path scenePath) : m_ScenePath(std::move(scenePath)) {}

        const std::filesystem::path &GetScenePath() const {
            return m_ScenePath;
        }

    private:
        std::filesystem::path m_ScenePath;
    };
}
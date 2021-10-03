#pragma once

#include "Engine/Core/shellpch.h"
#include "Engine/Project/Scene.h"

#include <entt/entt.hpp>

namespace Shell {
    class SceneEntity {
    public:
        SceneEntity(Ref<Scene> scene, entt::entity entity);

        void SetParent(SceneEntity * parent) { m_ParentEntity = parent; }
        [[nodiscard]] SceneEntity * GetParent() const { return m_ParentEntity; }

        void AddChild(SceneEntity * child) { m_ChildEntities.push_back(child); }
        std::vector<SceneEntity *>& GetChildren() { return m_ChildEntities; }

    private:
        Ref<Scene> m_Scene;
        entt::entity m_Entity;

        SceneEntity * m_ParentEntity;
        std::vector<SceneEntity *> m_ChildEntities;
    };
}
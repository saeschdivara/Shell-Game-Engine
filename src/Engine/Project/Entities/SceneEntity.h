#pragma once

#include "Engine/Core/shellpch.h"
#include "Engine/Project/Scene.h"

#include <entt/entt.hpp>

namespace Shell {
    class SceneEntity {
    public:
        SceneEntity(Ref<Scene> scene, const std::string & name, entt::entity entity);

        [[nodiscard]] std::string GetName() const { return m_Name; }
        void SetName(std::string &name) { m_Name = name; }

        void SetParent(SceneEntity * parent) { m_ParentEntity = parent; }
        [[nodiscard]] SceneEntity * GetParent() const { return m_ParentEntity; }

        void AddChild(SceneEntity * child) {
            child->SetParent(this);
            m_ChildEntities.push_back(child);
        }
        std::vector<SceneEntity *>& GetChildren() { return m_ChildEntities; }

        [[nodiscard]] entt::entity GetEnity() const { return m_Entity; }

    private:
        Ref<Scene> m_Scene;
        std::string m_Name;
        entt::entity m_Entity;

        SceneEntity * m_ParentEntity;
        std::vector<SceneEntity *> m_ChildEntities;
    };
}
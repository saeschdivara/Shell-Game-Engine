#pragma once

#include "Engine/Core/shellpch.h"
#include "Engine/Project/Scene.h"
#include "Engine/Utils/Uuid.h"

#include <entt/entt.hpp>

namespace Shell {
    class SceneEntity {
    public:
        SceneEntity(Ref<Scene> scene, const std::string & name, entt::entity entity);
        SceneEntity(Ref<Scene> scene, const std::string & name, const Uuid & id, entt::entity entity);

        [[nodiscard]] std::string GetName() const { return m_Name; }
        void SetName(std::string &name) { m_Name = name; }

        [[nodiscard]] const Uuid & GetUuid() const {
            return m_UUID;
        }

        void SetParent(SceneEntity * parent) { m_ParentEntity = parent; }
        [[nodiscard]] SceneEntity * GetParent() const { return m_ParentEntity; }

        void AddChild(SceneEntity * child) {
            child->SetParent(this);
            m_ChildEntities.push_back(child);
        }
        std::vector<SceneEntity *>& GetChildren() { return m_ChildEntities; }
        bool HasChildren() { return !m_ChildEntities.empty(); }

        [[nodiscard]] entt::entity GetEnity() const { return m_Entity; }

    private:
        Ref<Scene> m_Scene;
        std::string m_Name;
        Uuid m_UUID;
        entt::entity m_Entity;

        SceneEntity * m_ParentEntity;
        std::vector<SceneEntity *> m_ChildEntities;
    };
}
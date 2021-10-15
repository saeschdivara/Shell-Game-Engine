#pragma once

#include "Engine/Project/Entities/SceneEntity.h"
#include <entt/entt.hpp>

namespace Shell {
    class EntityManager {
    public:
        SceneEntity * CreateEntity(Ref<Scene> scene, const std::string & name);

        template <typename... Components>
        auto GetComponentView()
        {
            return m_Registry.view<Components...>({});
        }

        template <typename... Components>
        bool HasComponent(SceneEntity * entity)
        {
            return m_Registry.any_of<Components...>(entity->GetEnity());
        }

        template <typename... Components>
        auto& GetComponent(SceneEntity * entity)
        {
            return m_Registry.get<Components...>(entity->GetEnity());
        }

        template <typename Component>
        auto& AddComponent(SceneEntity * entity, auto&&... args) {
            return m_Registry.emplace<Component>(entity->GetEnity(), std::forward<decltype(args)>(args)...);
        }

    private:
        entt::registry m_Registry;
    };
}
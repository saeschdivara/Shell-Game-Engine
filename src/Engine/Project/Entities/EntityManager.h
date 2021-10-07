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

        template <typename Component>
        auto& AddComponent(SceneEntity * entity, auto&&... args) {
            return m_Registry.emplace<Component>(entity->GetEnity(), std::forward<decltype(args)>(args)...);
        }

    private:
        entt::registry m_Registry;
    };
}
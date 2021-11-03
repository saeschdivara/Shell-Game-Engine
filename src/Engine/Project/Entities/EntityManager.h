#pragma once

#include "Engine/Project/Entities/SceneEntity.h"
#include <entt/entt.hpp>

namespace Shell {
    class EntityManager {
    public:
        static Ref<EntityManager> Instance();

        SceneEntity * CreateEntity(Ref<Scene> scene, const std::string & name);
        SceneEntity * CreateEmptyEntity(Ref<Scene> scene, const std::string & name, const Uuid & id);

        template <typename... Components>
        auto GetComponentView()
        {
            return m_Registry.view<Components...>({});
        }

        template <typename... Components>
        bool HasComponent(SceneEntity * entity)
        {
            return m_Registry.any_of<Components...>(entity->GetEntity());
        }

        template <typename... Components>
        auto& GetComponent(SceneEntity * entity)
        {
            return m_Registry.get<Components...>(entity->GetEntity());
        }

        template <typename Component>
        auto& AddComponent(SceneEntity * entity, auto&&... args) {
            return m_Registry.emplace<Component>(entity->GetEntity(), std::forward<decltype(args)>(args)...);
        }

    private:
        static Ref<EntityManager> m_Instance;

        entt::registry m_Registry;
    };
}
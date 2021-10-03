#pragma once

#include "Engine/Project/Entities/SceneEntity.h"
#include <entt/entt.hpp>

namespace Shell {
    class EntityManager {
    public:
        SceneEntity * CreateEntity(Ref<Scene> scene);

    private:
        entt::registry m_Registry;
    };
}
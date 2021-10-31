#include "EntityManager.h"

#include "Engine/Core/Profiling.h"
#include "Engine/Project/Entities/Components.h"

#include <utility>

namespace Shell {
    Ref<EntityManager> EntityManager::m_Instance = nullptr;

    Ref<EntityManager> EntityManager::Instance() {
        if (!m_Instance) {
            m_Instance = CreateRef<EntityManager>();
        }

        return m_Instance;
    }

    SceneEntity *EntityManager::CreateEntity(Ref<Scene> scene, const std::string & name) {
        OPTICK_EVENT();

        auto entity = m_Registry.create();
        auto sceneEntity = new SceneEntity(std::move(scene), name, entity);

        // every scene entity has at least a transform component
        m_Registry.emplace<TransformComponent>(entity);

        return sceneEntity;
    }

    SceneEntity *EntityManager::CreateEmptyEntity(Ref<Scene> scene, const std::string &name, const Uuid & id) {
        OPTICK_EVENT();

        auto entity = m_Registry.create();
        return new SceneEntity(std::move(scene), name, id, entity);
    }
}
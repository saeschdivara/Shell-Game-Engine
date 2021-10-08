#include "EntityManager.h"
#include "Engine/Project/Entities/Components.h"

namespace Shell {
    SceneEntity *EntityManager::CreateEntity(Ref<Scene> scene, const std::string & name) {
        auto entity = m_Registry.create();
        auto sceneEntity = new SceneEntity(scene, name, entity);

        scene->GetEntities().push_back(sceneEntity);
        scene->GetEntityTree().push_back(sceneEntity);

        // every scene entity has at least a transform component
        m_Registry.emplace<TransformComponent>(entity);

        return sceneEntity;
    }
}
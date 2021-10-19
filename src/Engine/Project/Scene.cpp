#include "Scene.h"

#include <utility>

#include "Engine/Project/Entities/SceneEntity.h"

namespace Shell {

    Scene::Scene(std::string name, Uuid uuid) : m_Name(std::move(name)), m_UUID(uuid) {
    }

    std::string &Scene::GetName() {
        return m_Name;
    }

    const Uuid &Scene::GetUuid() const {
        return m_UUID;
    }

    std::vector<SceneEntity *> &Scene::GetEntities()  {
        return m_Entities;
    }

    std::vector<SceneEntity *> &Scene::GetEntityTree() {
        return m_EntityTree;
    }

    void Scene::AddEntity(SceneEntity * entity) {
        m_Entities.push_back(entity);
        m_EntityTree.push_back(entity);
    }
}
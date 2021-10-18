#include "Scene.h"

#include <utility>

#include "Engine/Project/Entities/SceneEntity.h"

namespace Shell {

    Scene::Scene(std::string name, Uuid uuid) : m_Name(std::move(name)), m_UUID(uuid) {
    }

    std::string &Scene::GetName() {
        return m_Name;
    }

    std::vector<SceneEntity *> &Scene::GetEntities()  {
        return m_Entities;
    }

    std::vector<SceneEntity *> &Scene::GetEntityTree() {
        return m_EntityTree;
    }

    const Uuid &Scene::GetUuid() const {
        return m_UUID;
    }
}
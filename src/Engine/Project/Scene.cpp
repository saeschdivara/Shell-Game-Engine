#include "Scene.h"

#include "Engine/Project/Entities/SceneEntity.h"

namespace Shell {

    std::vector<SceneEntity *> &Scene::GetEntityTree() {
        return m_EntityTree;
    }
}
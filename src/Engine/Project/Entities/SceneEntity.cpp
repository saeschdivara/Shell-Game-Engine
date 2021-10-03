#include "SceneEntity.h"

namespace Shell {
    SceneEntity::SceneEntity(Ref<Scene> scene, entt::entity entity)
    : m_Scene(scene), m_Entity(entity), m_ParentEntity(nullptr) {}
}
#include "SceneEntity.h"

namespace Shell {
    SceneEntity::SceneEntity(Ref<Scene> scene, const std::string & name, entt::entity entity)
    : m_Scene(scene), m_Name(name), m_UUID(Uuid::Create()), m_Entity(entity), m_ParentEntity(nullptr) {}
}
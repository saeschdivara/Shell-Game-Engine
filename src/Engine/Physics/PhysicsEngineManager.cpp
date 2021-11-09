#include "PhysicsEngineManager.h"

#include "Engine/Core/Profiling.h"
#include "Engine/Project/SceneBlueprint.h"
#include "Engine/Project/Entities/EntityManager.h"

#include <box2d/box2d.h>

namespace Shell::Physics {

    Ref <PhysicsEngineManager> PhysicsEngineManager::m_Instance = nullptr;

    struct Data {
        b2World * World;
    };

    PhysicsEngineManager::PhysicsEngineManager() : m_Data(new Data) {
    }

    PhysicsEngineManager::~PhysicsEngineManager() {
        delete m_Data;
    }

    Ref <PhysicsEngineManager> PhysicsEngineManager::Instance() {
        if (!m_Instance) {
            m_Instance = Shell::CreateRef<PhysicsEngineManager>();
        }

        return m_Instance;
    }

    void PhysicsEngineManager::Init() {
        OPTICK_CATEGORY(OPTICK_FUNC, Optick::Category::Physics);

        b2Vec2 gravity(0.0f, -10.0f);
        m_Data->World = new b2World(gravity);
    }

    void PhysicsEngineManager::InitScene(Ref<SceneBlueprint> scene) {
        auto view = EntityManager::Instance()->GetComponentView<TransformComponent, RigidBody2DComponent>();
        for (auto &&[entity, transform, rigidBody]: view.each()) {
            CreateRigidBody(transform.Translation, transform.Scale, rigidBody);
        }
    }

    void PhysicsEngineManager::CreateRigidBody(const glm::vec2 &position, const glm::vec2 &boxShape, RigidBody2DComponent body2DComponent) {
        OPTICK_CATEGORY(OPTICK_FUNC, Optick::Category::Physics);

        b2BodyDef bodyDefinition;
        bodyDefinition.type = static_cast<b2BodyType>(body2DComponent.BodyType);
        bodyDefinition.position.Set(position.x, position.y);

        b2Body* body = m_Data->World->CreateBody(&bodyDefinition);

        b2PolygonShape bodyShape;
        bodyShape.SetAsBox(boxShape.x, boxShape.y);

        body->CreateFixture(&bodyShape, body2DComponent.Mass);
    }
}

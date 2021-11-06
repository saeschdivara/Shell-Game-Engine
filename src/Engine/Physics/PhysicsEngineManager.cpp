#include "PhysicsEngineManager.h"

#include "Engine/Core/Profiling.h"

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

    void PhysicsEngineManager::CreateRigidBody(const glm::vec2 &position, const glm::vec2 &boxShape) {
        OPTICK_CATEGORY(OPTICK_FUNC, Optick::Category::Physics);

        b2BodyDef bodyDefinition;
        bodyDefinition.position.Set(position.x, position.y);

        b2Body* body = m_Data->World->CreateBody(&bodyDefinition);

        b2PolygonShape bodyShape;
        bodyShape.SetAsBox(boxShape.x, boxShape.y);

        body->CreateFixture(&bodyShape, 0.0f);
    }
}

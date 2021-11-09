#pragma once

#include "Engine/Core/shellpch.h"
#include "Engine/Project/Entities/Components.h"

#include <glm/glm.hpp>

namespace Shell {
    class SceneBlueprint;
}

namespace Shell::Physics {

    struct Data;

    class PhysicsEngineManager {
    public:
        static Ref<PhysicsEngineManager> Instance();

        PhysicsEngineManager();
        ~PhysicsEngineManager();

        void Init();
        void InitScene(Ref<SceneBlueprint> scene);

        void CreateRigidBody(const glm::vec2 & position, const glm::vec2 & boxShape, RigidBody2DComponent body2DComponent);

    private:
        static Ref<PhysicsEngineManager> m_Instance;

        Data * m_Data;
    };
}

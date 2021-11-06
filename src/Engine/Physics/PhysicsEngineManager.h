#pragma once

#include "Engine/Core/shellpch.h"

#include <glm/glm.hpp>

namespace Shell::Physics {

    struct Data;

    class PhysicsEngineManager {
    public:
        static Ref<PhysicsEngineManager> Instance();

        PhysicsEngineManager();
        ~PhysicsEngineManager();

        void Init();

        void CreateRigidBody(const glm::vec2 & position, const glm::vec2 & boxShape);

    private:
        static Ref<PhysicsEngineManager> m_Instance;

        Data * m_Data;
    };
}

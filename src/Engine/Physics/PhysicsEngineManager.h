#pragma once

#include "Engine/Core/shellpch.h"

namespace Shell::Physics {

    struct Data;

    class PhysicsEngineManager {
    public:
        static Ref<PhysicsEngineManager> Instance();

        PhysicsEngineManager();
        ~PhysicsEngineManager();

        void Init();

    private:
        static Ref<PhysicsEngineManager> m_Instance;

        Data * m_Data;
    };
}

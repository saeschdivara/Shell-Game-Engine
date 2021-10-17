#pragma once

#include "Engine/Core/shellpch.h"

namespace Shell {

    class SceneEntity;

    class Scene {
    public:
        Scene(std::string name);

        [[nodiscard]] std::string & GetName();

        std::vector<SceneEntity *>& GetEntities();
        std::vector<SceneEntity *>& GetEntityTree();

    private:
        std::string m_Name;

        std::vector<SceneEntity *> m_Entities;   // contains all entities
        std::vector<SceneEntity *> m_EntityTree; // contains only the top level entities
    };
}



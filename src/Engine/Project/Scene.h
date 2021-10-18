#pragma once

#include "Engine/Core/shellpch.h"
#include "Engine/Utils/Uuid.h"

namespace Shell {

    class SceneEntity;

    class Scene {
    public:
        Scene(std::string name, Uuid uuid);

        [[nodiscard]] std::string & GetName();
        const Uuid &GetUuid() const;

        std::vector<SceneEntity *>& GetEntities();
        std::vector<SceneEntity *>& GetEntityTree();

    private:
        std::string m_Name;
        Uuid m_UUID;

        std::vector<SceneEntity *> m_Entities;   // contains all entities
        std::vector<SceneEntity *> m_EntityTree; // contains only the top level entities
    };
}



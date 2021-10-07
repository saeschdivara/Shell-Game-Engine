#pragma once

namespace Shell {

    class SceneEntity;

    class Scene {
    public:
        std::vector<SceneEntity *>& GetEntities() { return m_Entities; }
        std::vector<SceneEntity *>& GetEntityTree();

    private:
        std::vector<SceneEntity *> m_Entities;   // contains all entities
        std::vector<SceneEntity *> m_EntityTree; // contains only the top level entities
    };
}



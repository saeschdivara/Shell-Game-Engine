#pragma once

class SceneEntity;

namespace Shell {

    class Scene {
    public:
        std::vector<SceneEntity *>& GetEntities() { return m_Entities; }
        std::vector<SceneEntity *>& GetEntityTree() { return m_EntityTree; }

    private:
        std::vector<SceneEntity *> m_Entities;   // contains all entities
        std::vector<SceneEntity *> m_EntityTree; // contains only the top level entities
    };
}



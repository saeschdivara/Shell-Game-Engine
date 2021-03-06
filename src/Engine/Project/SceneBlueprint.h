#pragma once

#include "Engine/Project/Scene.h"

namespace Shell {

    class SceneBlueprint : public Scene {
    public:
        SceneBlueprint(const std::string &name);
        SceneBlueprint(const std::string &name, const Uuid &id);
    };
}



#pragma once

#include <Engine/Project/SceneBlueprint.h>

namespace Shell::Editor {

    class SceneSerializer {
    public:
        static void SerializeToFile(Ref<SceneBlueprint> sceneBlueprint);
        static Ref<SceneBlueprint> DeserializeFromFile(const std::filesystem::path & path);
    private:
        SceneSerializer() = default;
    };

}

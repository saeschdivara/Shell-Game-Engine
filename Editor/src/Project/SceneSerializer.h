#pragma once

#include <Engine/Project/SceneBlueprint.h>

namespace Shell::Editor {

    class SceneSerializer {
    public:
        static void SerializeToFile(const std::filesystem::path &path, const Ref<SceneBlueprint>& sceneBlueprint);
        static Ref<SceneBlueprint> DeserializeFromFile(const std::filesystem::path & path);
    private:
        SceneSerializer() = default;
    };

}

#include "SceneSerializer.h"

namespace Shell::Editor {
    void SceneSerializer::SerializeToFile(Ref<SceneBlueprint> sceneBlueprint) {
    }

    Ref <SceneBlueprint> SceneSerializer::DeserializeFromFile(const std::filesystem::path &path) {
        return Shell::Ref<SceneBlueprint>();
    }
}
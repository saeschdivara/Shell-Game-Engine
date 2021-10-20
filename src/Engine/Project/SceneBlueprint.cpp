#include "SceneBlueprint.h"

namespace Shell {

    SceneBlueprint::SceneBlueprint(const std::string &name) : Scene(name, Uuid::Create()) {}

    SceneBlueprint::SceneBlueprint(const std::string &name, const Uuid & id) : Scene(name, id) {}

}
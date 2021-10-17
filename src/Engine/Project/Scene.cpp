#include "Scene.h"

#include <utility>

#include "Engine/Project/Entities/SceneEntity.h"

namespace Shell {

    Scene::Scene(std::string name) : m_Name(std::move(name)) {
//        std::random_device rd;
//        auto seed_data = std::array<int, std::mt19937::state_size> {};
//        std::generate(std::begin(seed_data), std::end(seed_data), std::ref(rd));
//        std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
//        std::mt19937 generator(seq);
//        uuids::uuid_random_generator gen{generator};
//
    }

    std::string &Scene::GetName() {
        return m_Name;
    }

    std::vector<SceneEntity *> &Scene::GetEntities()  {
        return m_Entities;
    }

    std::vector<SceneEntity *> &Scene::GetEntityTree() {
        return m_EntityTree;
    }
}
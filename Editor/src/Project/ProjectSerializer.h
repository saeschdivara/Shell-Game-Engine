#pragma once

#include <Engine/Project/Project.h>

namespace Shell {

    class ProjectSerializer {
    public:
        static void SerializeToFile(Project * project);
        static Project * DeserializeFromFile(const std::filesystem::path & projectPath);
    private:
        ProjectSerializer() = default;
    };
}

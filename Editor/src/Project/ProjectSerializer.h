#pragma once

#include <Engine/Project/Project.h>

namespace Shell {

    class ProjectSerializer {
    public:
        static void SerializeToFile(Project * project);
    private:
        ProjectSerializer() = default;
    };
}

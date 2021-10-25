#pragma once

#include "Engine/Core/shellpch.h"

namespace Shell::Scripting {

    class VisualStudioProjectManager {
    public:
        void CreateProject(const std::filesystem::path & projectPath, const std::string & projectName);
    };
}

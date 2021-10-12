#pragma once

#include "Engine/Core/shellpch.h"
#include "Engine/Project/ProjectSettings.h"

namespace Shell {
    class Project {
    public:
        Project(std::wstring name, std::filesystem::path path);

        [[nodiscard]] const std::string GetNameAsSimpleString() const;
        [[nodiscard]] const std::wstring &GetName() const;
        [[nodiscard]] const std::filesystem::path &GetPath() const;
        [[nodiscard]] ProjectSettings *GetSettings() const;

    private:
        std::wstring m_Name;
        std::filesystem::path m_Path;
        ProjectSettings * m_Settings;
    };
}



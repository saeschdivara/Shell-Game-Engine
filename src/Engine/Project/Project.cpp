#include "Project.h"

#include <utility>

namespace Shell {

    Project::Project(std::wstring name, std::filesystem::path path)
    : m_Name(std::move(name)), m_Path(std::move(path)), m_Settings(nullptr)
    {}

    const std::wstring &Project::GetName() const {
        return m_Name;
    }

    const std::filesystem::path &Project::GetPath() const {
        return m_Path;
    }

    ProjectSettings *Project::GetSettings() const {
        return m_Settings;
    }
}
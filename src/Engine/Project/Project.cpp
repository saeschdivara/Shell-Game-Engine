#include "Project.h"

namespace Shell {

    Project::Project(const std::wstring &name, std::filesystem::path path)
    : m_Name(name), m_Path(std::move(path)), m_Settings(nullptr)
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
#include "Project.h"

#include <utility>

namespace Shell {

    Project::Project(std::wstring name, std::filesystem::path path)
    : m_Name(std::move(name)), m_Path(std::move(path)), m_Settings(new ProjectSettings)
    {
        m_Settings->SetRenderingApi(OperatingSystem::Windows, RenderAPI::OpenGL);
        m_Settings->SetRenderingApi(OperatingSystem::Linux, RenderAPI::OpenGL);
        m_Settings->SetRenderingApi(OperatingSystem::MacOS, RenderAPI::OpenGL);
    }

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
#pragma once

#include <Engine/Core/shellpch.h>
#include <Engine/Core/Rendering/API.h>

namespace Shell {

    class ProjectSettings {
    public:
        ProjectSettings() = default;

        [[nodiscard]] const std::unordered_map<OperatingSystem, RenderAPI> &getOperatingSystemRenderer() const;
        void SetRenderingApi(OperatingSystem os, RenderAPI api);

        [[nodiscard]] const std::string &GetAppLibraryPath() const;
        void SetAppLibraryPath(const std::string &mAppLibraryPath);

    private:
        std::string m_AppLibraryPath;
        std::unordered_map<OperatingSystem, RenderAPI> m_OperatingSystemRenderer;
    };
}



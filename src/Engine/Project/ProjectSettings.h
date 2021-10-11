#pragma once

#include <Engine/Core/shellpch.h>
#include <Engine/Core/Rendering/API.h>

namespace Shell {

    class ProjectSettings {
    public:
        [[nodiscard]] const std::unordered_map<OperatingSystem, RenderAPI> &getOperatingSystemRenderer() const;
        void SetRenderingApi(OperatingSystem os, RenderAPI api);

    private:
        std::unordered_map<OperatingSystem, RenderAPI> m_OperatingSystemRenderer;
    };
}



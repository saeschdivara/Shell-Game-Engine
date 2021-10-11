#include "ProjectSettings.h"

namespace Shell {

    const std::unordered_map<OperatingSystem, RenderAPI> &ProjectSettings::getOperatingSystemRenderer() const {
        return m_OperatingSystemRenderer;
    }

    void ProjectSettings::SetRenderingApi(OperatingSystem os, RenderAPI api) {
        m_OperatingSystemRenderer.insert_or_assign(os, api);
    }
}
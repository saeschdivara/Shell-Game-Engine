#include "EntityPropsPanel.h"

#include <imgui.h>

namespace Shell::Editor {

    void EntityPropsPanel::Render() {
        ImGui::Begin("Stats");

        std::string name = "None";
//        if (m_SelectedEntity)
//            name = m_SelectedEntity->GetName();
        ImGui::Text("Hovered Entity: %s", name.c_str());

        ImGui::End();
    }
}
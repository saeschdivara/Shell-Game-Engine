#include "EntityPropsPanel.h"
#include "UI/UILayer.h"

#include <imgui.h>

namespace Shell::Editor {

    void EntityPropsPanel::Render() {
        ImGui::Begin("Stats");

        std::string name = "None";
        if (m_UiState->SelectedEntity)
            name = m_UiState->SelectedEntity->GetName();
        ImGui::Text("Hovered Entity: %s", name.c_str());

        ImGui::End();
    }
}
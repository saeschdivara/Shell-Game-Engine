#include "EntityPropsPanel.h"
#include "UI/UILayer.h"

#include <Engine/Project/Entities/Components.h>

#include <imgui.h>

namespace Shell::Editor {

    void EntityPropsPanel::Render() {
        ImGui::Begin("Stats");

        std::string name = "None";
        if (m_UiState->SelectedEntity) {
            name = m_UiState->SelectedEntity->GetName();

            if (m_UiState->EntityManager->HasComponent<TransformComponent>(m_UiState->SelectedEntity)) {
                static float input[3];
                ImGui::DragFloat3("##value", input, 0.01f);
            }
        }
        ImGui::Text("Hovered Entity: %s", name.c_str());

        ImGui::End();
    }
}
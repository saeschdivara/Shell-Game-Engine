#include "EntityPropsPanel.h"
#include "UI/UILayer.h"

#include <Engine/Project/Entities/Components.h>

#include <imgui.h>

namespace Shell::Editor {

    static float transformValues[] = { 0.0, 0.0 };
    static bool isValuesInitialized = false;

    void EntityPropsPanel::Render() {
        ImGui::Begin("Stats");

        if (m_UiState->SelectedEntity) {
            if (m_UiState->EntityManager->HasComponent<TransformComponent>(m_UiState->SelectedEntity)) {
                RenderTransformComponent();
            }
        } else {
            isValuesInitialized = false;
        }

        ImGui::End();
    }

    void EntityPropsPanel::RenderTransformComponent() {
        auto& transform = m_UiState->EntityManager->GetComponent<TransformComponent>(m_UiState->SelectedEntity);

        if (!isValuesInitialized || m_UiState->ChangedEntity) {
            isValuesInitialized = true;
            transformValues[0] = transform.Translation.x;
            transformValues[1] = transform.Translation.y;
        }

        ImGui::Text("Position");
        ImGui::SameLine();
        ImGui::DragFloat2("##value", transformValues, 0.01f);

        transform.Translation.x = transformValues[0];
        transform.Translation.y = transformValues[1];
    }
}
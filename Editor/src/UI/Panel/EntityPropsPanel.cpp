#include "EntityPropsPanel.h"
#include "UI/UILayer.h"

#include <Engine/Project/Entities/Components.h>

#include <imgui.h>

namespace Shell::Editor {

    static float transformValues[] = { 0.0, 0.0 };
    static float colorInput[] = { 0.0, 0.0, 0.0, 1.0 };

    static bool isValuesInitialized = false;

    void EntityPropsPanel::Render() {
        ImGui::Begin("Stats");

        if (m_UiState->SelectedEntity) {
            if (m_UiState->EntityManager->HasComponent<TransformComponent>(m_UiState->SelectedEntity)) {
                RenderTransformComponent();
            }
            if (m_UiState->EntityManager->HasComponent<SpriteComponent>(m_UiState->SelectedEntity)) {
                RenderSpriteComponent();
            }

            if (!isValuesInitialized || m_UiState->ChangedEntity) {
                isValuesInitialized = true;
            }
        } else {
            isValuesInitialized = false;
        }

        ImGui::End();
    }

    void EntityPropsPanel::RenderTransformComponent() {
        auto& transform = m_UiState->EntityManager->GetComponent<TransformComponent>(m_UiState->SelectedEntity);

        if (!isValuesInitialized || m_UiState->ChangedEntity) {
            transformValues[0] = transform.Translation.x;
            transformValues[1] = transform.Translation.y;
        }

        ImGui::Text("Position");
        ImGui::SameLine();
        ImGui::DragFloat2("##value", transformValues, 0.01f);

        transform.Translation.x = transformValues[0];
        transform.Translation.y = transformValues[1];
    }

    void EntityPropsPanel::RenderSpriteComponent() {
        auto& sprite = m_UiState->EntityManager->GetComponent<SpriteComponent>(m_UiState->SelectedEntity);

        if (!isValuesInitialized || m_UiState->ChangedEntity) {
            colorInput[0] = sprite.Color.r;
            colorInput[1] = sprite.Color.g;
            colorInput[2] = sprite.Color.b;
            colorInput[3] = sprite.Color.a;
        }

        ImGui::Text("Color");
        ImGui::SameLine();
        ImGui::ColorEdit4("", colorInput, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);

        sprite.Color.r = colorInput[0];
        sprite.Color.g = colorInput[1];
        sprite.Color.b = colorInput[2];
        sprite.Color.a = colorInput[3];
    }
}
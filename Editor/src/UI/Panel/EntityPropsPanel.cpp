#include "EntityPropsPanel.h"
#include "UI/UILayer.h"

#include <Engine/Project/Entities/Components.h>

#include <imgui.h>

namespace Shell::Editor {

    static float transformValues[] = { 0.0, 0.0 };
    static float scaleValues[] = { 0.0, 0.0 };
    static float rotationValue = 0.0f;
    static float colorInput[] = { 0.0, 0.0, 0.0, 1.0 };

    static char* scriptFilePath = new char[2048];
    static char* scriptClassName = new char[2048];

    static bool isValuesInitialized = false;

    EntityPropsPanel::EntityPropsPanel() {
        std::memset(scriptFilePath, 0, 2048);
        std::memset(scriptClassName, 0, 2048);
    }

    void EntityPropsPanel::Render() {
        ImGui::Begin("Stats");

        if (m_UiState->SelectedEntity) {
            if (EntityManager::Instance()->HasComponent<TransformComponent>(m_UiState->SelectedEntity)) {
                RenderTransformComponent();
            }
            if (EntityManager::Instance()->HasComponent<SpriteComponent>(m_UiState->SelectedEntity)) {
                RenderSpriteComponent();
            }
            if (EntityManager::Instance()->HasComponent<ScriptingComponent>(m_UiState->SelectedEntity)) {
                RenderScriptingComponent();
            }

                if (ImGui::BeginPopupContextWindow("component context"))
                {
                    if (ImGui::MenuItem("Scripting", NULL, false)) {
                        EntityManager::Instance()->AddComponent<ScriptingComponent>(m_UiState->SelectedEntity);
                    }

                    ImGui::EndPopup();
                }

            if (ImGui::Button("Add")) {
                ImGui::OpenPopup("component context");
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
        auto& transform = EntityManager::Instance()->GetComponent<TransformComponent>(m_UiState->SelectedEntity);

        if (!isValuesInitialized || m_UiState->ChangedEntity) {
            transformValues[0] = transform.Translation.x;
            scaleValues[1] = transform.Scale.y;

            scaleValues[0] = transform.Scale.x;
            scaleValues[1] = transform.Scale.y;

            rotationValue = transform.Rotation.z;
        }

        ImGui::Text("Position");
        ImGui::SameLine();
        ImGui::DragFloat2("##position", transformValues, 0.01f);

        ImGui::Text("Scale");
        ImGui::SameLine();
        ImGui::DragFloat2("##scale", scaleValues, 0.01f);

        ImGui::Text("Rotation");
        ImGui::SameLine();
        ImGui::DragFloat("##rotation", &rotationValue, 0.01f);
        ImGui::Separator();

        transform.Translation.x = transformValues[0];
        transform.Translation.y = transformValues[1];

        transform.Scale.x = scaleValues[0];
        transform.Scale.y = scaleValues[1];

        transform.Rotation.z = rotationValue;
    }

    void EntityPropsPanel::RenderSpriteComponent() {
        auto& sprite = EntityManager::Instance()->GetComponent<SpriteComponent>(m_UiState->SelectedEntity);

        if (!isValuesInitialized || m_UiState->ChangedEntity) {
            colorInput[0] = sprite.Color.r;
            colorInput[1] = sprite.Color.g;
            colorInput[2] = sprite.Color.b;
            colorInput[3] = sprite.Color.a;
        }

        ImGui::Text("Color");
        ImGui::SameLine();
        ImGui::ColorEdit4("", colorInput, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
        ImGui::Separator();

        sprite.Color.r = colorInput[0];
        sprite.Color.g = colorInput[1];
        sprite.Color.b = colorInput[2];
        sprite.Color.a = colorInput[3];
    }

    void EntityPropsPanel::RenderScriptingComponent() {
        auto& scripting = EntityManager::Instance()->GetComponent<ScriptingComponent>(m_UiState->SelectedEntity);

        if (!isValuesInitialized || m_UiState->ChangedEntity) {
            scriptFilePath = scripting.Path.data();
            scriptClassName = scripting.ClassName.data();
        }

        ImGui::InputText("Script Path", scriptFilePath, 2047);
        ImGui::InputText("Class Name", scriptClassName, 2047);
        ImGui::Separator();

        scripting.Path = scriptFilePath;
        scripting.ClassName = scriptClassName;
    }
}
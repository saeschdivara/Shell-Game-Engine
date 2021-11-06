#include "EntityPropsPanel.h"
#include "UI/UILayer.h"

#include <Engine/Physics/PhysicsEngineManager.h>
#include <Engine/Project/Entities/Components.h>

#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>

namespace Shell::Editor {

    static float transformValues[] = { 0.0, 0.0 };
    static float scaleValues[] = { 0.0, 0.0 };
    static float rotationValue = 0.0f;
    static float colorInput[] = { 0.0, 0.0, 0.0, 1.0 };

    static std::string scriptFilePath;
    static std::string scriptClassName;

    static float mass = 0.0f;
    const char * RIGID_BODY_TYPES[] = { "Dynamic", "Kinematic", "Static" };
    static const char* currentRigidBodyType = NULL;

    static bool isValuesInitialized = false;

    EntityPropsPanel::EntityPropsPanel() {
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
            if (EntityManager::Instance()->HasComponent<RigidBody2DComponent>(m_UiState->SelectedEntity)) {
                RenderRigidBody2DComponent();
            }

            if (ImGui::BeginPopupContextWindow("component context"))
            {
                if (ImGui::MenuItem("Scripting", NULL, false)) {
                    EntityManager::Instance()->AddComponent<ScriptingComponent>(m_UiState->SelectedEntity);
                }
                if (ImGui::MenuItem("Rigid Body", NULL, false)) {
                    EntityManager::Instance()->AddComponent<RigidBody2DComponent>(m_UiState->SelectedEntity);
                }
                if (ImGui::MenuItem("Box Collider", NULL, false)) {
                    EntityManager::Instance()->AddComponent<BoxCollider>(m_UiState->SelectedEntity);
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
            transformValues[1] = transform.Translation.y;

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
            scriptFilePath = scripting.Path;
            scriptClassName = scripting.ClassName;
        }

        ImGui::InputText("Script Path", &scriptFilePath);
        ImGui::InputText("Class Name", &scriptClassName);
        ImGui::Separator();

        scripting.Path = scriptFilePath;
        scripting.ClassName = scriptClassName;
    }

    void EntityPropsPanel::RenderRigidBody2DComponent() {
        auto& rigidBody = EntityManager::Instance()->GetComponent<RigidBody2DComponent>(m_UiState->SelectedEntity);

        if (!isValuesInitialized || m_UiState->ChangedEntity) {
            mass = rigidBody.Mass;
            currentRigidBodyType = RIGID_BODY_TYPES[static_cast<unsigned int>(rigidBody.BodyType)];
        }

        if (ImGui::BeginCombo("Type", currentRigidBodyType))
        {
            for (auto & bodyType : RIGID_BODY_TYPES)
            {
                bool isSelected = (currentRigidBodyType == bodyType); // You can store your selection however you want, outside or inside your objects
                if (ImGui::Selectable(bodyType, isSelected)) {
                    currentRigidBodyType = bodyType;
                }

                if (isSelected)
                    ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
            }

            ImGui::EndCombo();
        }

        ImGui::Text("Mass");
        ImGui::SameLine();
        ImGui::DragFloat("##mass", &mass, 0.01f);
        ImGui::Separator();

        rigidBody.Mass = mass;

        if (currentRigidBodyType == RIGID_BODY_TYPES[0]) {
            rigidBody.BodyType = RigidBodyType::DYNAMIC;
        }
        else if (currentRigidBodyType == RIGID_BODY_TYPES[1]) {
            rigidBody.BodyType = RigidBodyType::KINEMATIC;
        }
        else if (currentRigidBodyType == RIGID_BODY_TYPES[2]) {
            rigidBody.BodyType = RigidBodyType::STATIC;
        }
    }
}
#pragma once

#include <Engine/Core/Logger.h>
#include <Engine/Core/Layers/Layer.h>
#include <imgui.h>

namespace Sandbox {
    class SampleLayer : public Shell::Layer {
    public:
        SampleLayer() : Layer("Sample Layer") {}

        void OnUiRender() override {
            ImGui::Begin("My Window");
            ImGui::Text("Hello, world %d", 123);
            if (ImGui::Button("Save"))
                SHELL_DEBUG("Clicked save button");
            ImGui::End();
        }
    };
}
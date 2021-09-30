#include "UILayer.h"
#include <imgui.h>
#include <imgui_internal.h>

namespace Shell::Editor {

    EditorUILayer::EditorUILayer() : Layer("UI Layer") {}

    void EditorUILayer::OnUiRender() {
         ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
    }
}
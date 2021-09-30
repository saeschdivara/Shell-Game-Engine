#pragma once

#include <Engine/Core/Layers/Layer.h>

namespace Shell::Editor {

    class EditorUILayer : public Layer {
    public:
        EditorUILayer();

        void OnUiRender() override;
    };

}
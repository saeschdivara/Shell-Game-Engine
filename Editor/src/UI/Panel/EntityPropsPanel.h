#pragma once

#include "UI/Panel/Panel.h"

namespace Shell::Editor {

    class EntityPropsPanel : public Panel {
    public:
        EntityPropsPanel();
        void Render() override;

    private:
        void RenderTransformComponent();
        void RenderSpriteComponent();
        void RenderScriptingComponent();
    };
}



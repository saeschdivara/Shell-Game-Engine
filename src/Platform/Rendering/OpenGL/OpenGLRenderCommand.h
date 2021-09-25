#pragma once

#include "Engine/Core/Rendering/RenderCommand.h"

namespace Shell {

    class OpenGLRenderCommand : public RenderCommand {
    public:
        void SetClearColor(glm::vec4 &color) override;
        void Clear() override;

        void DrawIndexed(const Ref<BufferContainer> &bufferContainer) override;
    };
}



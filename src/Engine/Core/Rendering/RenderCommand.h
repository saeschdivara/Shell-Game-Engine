#pragma once

#include "Engine/Core/Rendering/BufferContainer.h"

#include <glm/glm.hpp>

namespace Shell {

    class RenderCommand {
    public:
        virtual void SetClearColor(glm::vec4 & color) = 0;
        virtual void Clear() = 0;

        virtual void DrawIndexed(const Ref<BufferContainer>& bufferContainer) = 0;

        static Ref<RenderCommand> Create();
    };

}



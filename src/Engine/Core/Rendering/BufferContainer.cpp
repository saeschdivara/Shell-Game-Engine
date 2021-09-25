#include "BufferContainer.h"

#include "Engine/Core/Rendering/Renderer.h"
#include "Platform/Rendering/OpenGL/OpenGLBufferContainer.h"

namespace Shell {

    Ref<BufferContainer> BufferContainer::Create() {
        switch (Renderer::Instance()->getCurrentApi()) {
            case RenderAPI::OpenGL:
                return CreateRef<OpenGLBufferContainer>();

            default:
                SHELL_CORE_ASSERT(false, "Render API implementation not found");
                return {};
        }
    }
}
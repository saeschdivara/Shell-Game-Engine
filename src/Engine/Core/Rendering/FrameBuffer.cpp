#include "FrameBuffer.h"

#include "Engine/Core/Rendering/Renderer.h"
#include "Platform/Rendering/OpenGL/OpenGLFrameBuffer.h"

namespace Shell {
    Ref <FrameBuffer> FrameBuffer::Create(const FrameBufferSpecification& specification) {
        switch (Renderer::Instance()->getCurrentApi()) {
            case RenderAPI::OpenGL:
                return CreateRef<OpenGLFrameBuffer>(specification);

            default:
                SHELL_CORE_ASSERT(false, "Render API implementation not found");
                return {};
        }
    }
}
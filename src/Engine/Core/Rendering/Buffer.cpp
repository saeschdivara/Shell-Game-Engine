#include "Buffer.h"

#include "Engine/Core/Rendering/Renderer.h"
#include "Platform/Rendering/OpenGL/OpenGLBuffer.h"

namespace Shell {

    Ref<VertexBuffer> VertexBuffer::Create(float *vertices, uint32_t size) {
        switch (Renderer::Instance()->getCurrentApi()) {
            case RenderAPI::OpenGL:
                return CreateRef<OpenGLVertexBuffer>(vertices, size);

            default:
                SHELL_CORE_ASSERT(false, "Render API implementation not found");
                return {};
        }
    }

    Ref<IndexBuffer> IndexBuffer::Create(uint32_t *vertices, uint32_t count) {
        switch (Renderer::Instance()->getCurrentApi()) {
            case RenderAPI::OpenGL:
                return CreateRef<OpenGLIndexBuffer>(vertices, count);

            default:
                SHELL_CORE_ASSERT(false, "Render API implementation not found");
                return {};
        }
    }
}

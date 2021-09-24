#include "Buffer.h"

#include "Engine/Core/Rendering/Renderer.h"
#include "Platform/Rendering/OpenGL/OpenGLBuffer.h"

namespace Shell {

    Ref<VertexBuffer> VertexBuffer::Create(float *vertices, uint32_t size) {
        auto api = Renderer::Instance()->getCurrentApi();
        switch (Renderer::Instance()->getCurrentApi()) {
            case RenderAPI::OpenGL:
                return CreateRef<OpenGLVertexBuffer>(vertices, size);

            default:
                SHELL_CORE_WARN("Render API implementation not found for {0}", api);
                return Ref<VertexBuffer>();
        }
    }

    Ref<IndexBuffer> IndexBuffer::Create(float *vertices, uint32_t size) {
        return Ref<IndexBuffer>();
    }
}

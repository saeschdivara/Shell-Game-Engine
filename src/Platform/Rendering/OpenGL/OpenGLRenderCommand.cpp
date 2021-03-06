#include "OpenGLRenderCommand.h"

#include "Engine/Core/Profiling.h"

#include <glad/glad.h>

namespace Shell {

    void OpenGLRenderCommand::SetViewport(uint32_t width, uint32_t height) {
        OPTICK_EVENT();

        glViewport(0, 0, width, height);
    }

    void OpenGLRenderCommand::SetClearColor(glm::vec4 &color) {
        OPTICK_EVENT();

        glClearColor(color.r, color.g, color.b, color.a);
    }

    void OpenGLRenderCommand::Clear() {
        OPTICK_EVENT();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the buffers
    }

    void OpenGLRenderCommand::DrawIndexed(const Ref<BufferContainer> &bufferContainer) {
        OPTICK_EVENT();

        glDrawElements(GL_TRIANGLES, bufferContainer->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    }
}
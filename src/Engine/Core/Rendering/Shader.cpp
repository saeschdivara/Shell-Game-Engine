#include "Shader.h"

#include "Engine/Core/Rendering/Renderer.h"
#include "Platform/Rendering/OpenGL/OpenGLShader.h"

namespace Shell {
    Ref<Shader> Shader::Create(const std::string &vertexSrc, const std::string &fragmentSrc) {
        switch (Renderer::Instance()->getCurrentApi()) {
            case RenderAPI::OpenGL:
                return CreateRef<OpenGLShader>(vertexSrc, fragmentSrc);

            default:
                SHELL_CORE_ASSERT(false, "Render API implementation not found");
                return {};
        }
    }
}
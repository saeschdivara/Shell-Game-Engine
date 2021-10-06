#include "Shader.h"

#include "Engine/Core/Rendering/Renderer.h"
#include "Platform/Rendering/OpenGL/OpenGLShader.h"

#include <fstream>

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

    Ref<Shader> Shader::CreateFromFiles(const std::string &vertexFilePath, const std::string &fragmentFilePath) {
        std::ifstream vertexFile(vertexFilePath);
        std::stringstream vertexBuffer;
        vertexBuffer << vertexFile.rdbuf();

        std::ifstream fragmentFile(fragmentFilePath);
        std::stringstream fragmentBuffer;
        fragmentBuffer << fragmentFile.rdbuf();

        return Create(vertexBuffer.str(), fragmentBuffer.str());
    }
}
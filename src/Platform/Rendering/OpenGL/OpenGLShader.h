#pragma once

#include "Engine/Core/Rendering/Shader.h"

namespace Shell {
    class OpenGLShader : public Shader {
    public:
        OpenGLShader(const std::string &vertexSrc, const std::string &fragmentSrc);
        ~OpenGLShader() override;

        void Bind() override;
        void Unbind() override;

        void SetUniform(const std::string &uniformName, const glm::mat4 &matrix) const override;

    private:
        uint32_t m_RendererID;
    };
}



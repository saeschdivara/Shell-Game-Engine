#pragma once

#include "Engine/Core/Rendering/Shader.h"

namespace Shell {
    class OpenGLShader : public Shader {
    public:
        OpenGLShader(const std::string &vertexSrc, const std::string &fragmentSrc);
        ~OpenGLShader() override;

        void Bind() override;
        void Unbind() override;

        void SetUniform(const std::string &uniformName, const glm::mat3 &matrix) const override;
        void SetUniform(const std::string &uniformName, const glm::mat4 &matrix) const override;

        void SetUniform(const std::string &uniformName, int intValue) const override;

        void SetUniform(const std::string &uniformName, float floatValue) const override;
        void SetUniform(const std::string &uniformName, const glm::vec2 &vec2) const override;
        void SetUniform(const std::string &uniformName, const glm::vec3 &vec3) const override;
        void SetUniform(const std::string &uniformName, const glm::vec4 &vec4) const override;

    private:
        uint32_t m_RendererID;
    };
}



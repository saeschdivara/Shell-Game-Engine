#pragma once

#include "Engine/Core/shellpch.h"

#include <glm/glm.hpp>

namespace Shell {
    class Shader {
    public:
        Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
        ~Shader();

        void Bind();
        void Unbind();

        void SetUniform(const std::string& uniformName, const glm::mat4& matrix) const;

    private:
        uint32_t m_RendererID;
    };
}
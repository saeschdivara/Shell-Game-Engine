#pragma once

#include "Engine/Core/shellpch.h"

#include <glm/glm.hpp>

namespace Shell {
    class Shader {
    public:
        virtual ~Shader() {}

        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        virtual void SetUniform(const std::string& uniformName, const glm::mat4& matrix) const = 0;

        static Ref<Shader> Create(const std::string &vertexSrc, const std::string &fragmentSrc);
    };
}
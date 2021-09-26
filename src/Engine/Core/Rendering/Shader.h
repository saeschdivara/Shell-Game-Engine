#pragma once

#include "Engine/Core/shellpch.h"

#include <glm/glm.hpp>

namespace Shell {
    class Shader {
    public:
        virtual ~Shader() {}

        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        virtual void SetUniform(const std::string& uniformName, const glm::mat3& matrix) const = 0;
        virtual void SetUniform(const std::string& uniformName, const glm::mat4& matrix) const = 0;

        virtual void SetUniform(const std::string &uniformName, int intValue)            const = 0;

        virtual void SetUniform(const std::string &uniformName, float floatValue)        const = 0;
        virtual void SetUniform(const std::string &uniformName, const glm::vec2 &vec2)   const = 0;
        virtual void SetUniform(const std::string &uniformName, const glm::vec3 &vec3)   const = 0;
        virtual void SetUniform(const std::string &uniformName, const glm::vec4 &vec4)   const = 0;

        static Ref<Shader> Create(const std::string &vertexSrc, const std::string &fragmentSrc);
    };
}
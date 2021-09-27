#pragma once

#include "Engine/Core/shellpch.h"

namespace Shell {

    class Texture {
    public:
        virtual ~Texture() {}
        [[nodiscard]] virtual uint32_t GetWidth() const = 0;
        [[nodiscard]] virtual uint32_t GetHeight() const = 0;

        virtual void Bind() const = 0;
    };

    class Texture2D : public Texture {
    public:
        static Ref<Texture2D> Create(const std::string & path);
    };

}
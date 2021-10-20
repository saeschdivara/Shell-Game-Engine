#pragma once

#include "Engine/Core/Rendering/Texture.h"

namespace Shell {

    class OpenGLTexture2D : public Texture2D {
    public:
        explicit OpenGLTexture2D(const std::string & path);
        ~OpenGLTexture2D() override;

        [[nodiscard]] uint32_t GetWidth() const override;
        [[nodiscard]] uint32_t GetHeight() const override;
        [[nodiscard]] std::string GetPath() const override;

        void Bind() const override;

    private:
        std::string m_Path;
        uint32_t m_Height;
        uint32_t m_Width;
        uint32_t m_RendererID;
    };
}



#pragma once

#include "Engine/Core/Rendering/Buffer.h"

namespace Shell {

    class OpenGLVertexBuffer : public VertexBuffer {
    public:
        OpenGLVertexBuffer(float * vertices, uint32_t size);
        ~OpenGLVertexBuffer() override;

        void Bind() override;
        void Unbind() override;

    private:
        uint32_t m_RendererID;
    };

    class OpenGLIndexBuffer : public IndexBuffer {
    public:
        OpenGLIndexBuffer(uint32_t * vertices, uint32_t size);
        ~OpenGLIndexBuffer() override;

        void Bind() override;
        void Unbind() override;

        uint32_t GetCount() const override { return m_VerticesCount; };

    private:
        uint32_t m_RendererID;
        uint32_t m_VerticesCount;
    };

}


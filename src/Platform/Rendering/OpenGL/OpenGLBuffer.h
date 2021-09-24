#pragma once

#include "Engine/Core/Rendering/Buffer.h"

namespace Shell {

    class OpenGLVertexBuffer : public VertexBuffer {
    public:
        OpenGLVertexBuffer(float * vertices, uint32_t size);
        ~OpenGLVertexBuffer() override;

        void Bind() override;
        void Unbind() override;

        void SetLayout(const BufferLayout& layout) override { m_Layout = layout; };
        BufferLayout GetLayout() const override { return m_Layout; };

    private:
        uint32_t m_RendererID;
        BufferLayout m_Layout;
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


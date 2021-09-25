#pragma once

#include "Engine/Core/Rendering/Buffer.h"

namespace Shell {

    class OpenGLVertexBuffer : public VertexBuffer {
    public:
        OpenGLVertexBuffer(float * vertices, uint32_t size);
        ~OpenGLVertexBuffer() override;

        void Bind() override;
        void Unbind() override;

        void SetLayout(const BufferLayout& layout) override {
            m_Layout = layout;
            m_IsLayoutSet = true;
        };

        [[nodiscard]] BufferLayout GetLayout() const override { return m_Layout; };
        [[nodiscard]] bool HasValidLayout() const override { return m_IsLayoutSet && !m_Layout.GetElements().empty(); };


    private:
        uint32_t m_RendererID;
        BufferLayout m_Layout;
        bool m_IsLayoutSet = false;
    };

    class OpenGLIndexBuffer : public IndexBuffer {
    public:
        OpenGLIndexBuffer(uint32_t * vertices, uint32_t size);
        ~OpenGLIndexBuffer() override;

        void Bind() override;
        void Unbind() override;

        [[nodiscard]] uint32_t GetCount() const override { return m_VerticesCount; };

    private:
        uint32_t m_RendererID;
        uint32_t m_VerticesCount;
    };

}


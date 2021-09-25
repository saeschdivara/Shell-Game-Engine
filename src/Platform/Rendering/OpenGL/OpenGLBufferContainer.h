#pragma once

#include "Engine/Core/Rendering/BufferContainer.h"

namespace Shell {

    class OpenGLBufferContainer : public BufferContainer {
    public:
        OpenGLBufferContainer();

        void Bind() override;
        void Unbind() override;

        void AddBuffer(Ref<Buffer> buffer) override;
        [[nodiscard]] Ref<IndexBuffer> GetIndexBuffer() const override { return m_IndexBuffer; }

    private:
        uint32_t m_RendererID;
        std::vector<Ref<Buffer>> m_Buffers;
        Ref<IndexBuffer> m_IndexBuffer;
    };
}



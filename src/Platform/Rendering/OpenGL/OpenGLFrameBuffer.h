#pragma once

#include "Engine/Core/Rendering/FrameBuffer.h"

namespace Shell {

    class OpenGLFrameBuffer : public FrameBuffer {
    public:
        OpenGLFrameBuffer(const FrameBufferSpecification& specification);

        virtual ~OpenGLFrameBuffer();

        [[nodiscard]] FrameBufferSpecification &GetSpecification() override {
            return m_Specification;
        }

        void Bind() override;
        void Unbind() override;

        void Recreate();

        [[nodiscard]] uint32_t GetColorAttachment() const override {
            return m_ColorAttachment;
        }

    private:
        uint32_t m_RendererID;
        uint32_t m_ColorAttachment;
        uint32_t m_DepthAttachment;
        FrameBufferSpecification m_Specification;
    };

}
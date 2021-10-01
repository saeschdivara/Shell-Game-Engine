#pragma once

#include "Engine/Core/Rendering/FrameBuffer.h"

namespace Shell {

    class OpenGLFrameBuffer : public FrameBuffer {
    public:
        OpenGLFrameBuffer(const FrameBufferSpecification& specification);

        virtual ~OpenGLFrameBuffer();

        [[nodiscard]] FrameBufferSpecification &GetSpecification() const override {
            return m_Specification;
        }

        void Recreate();

    private:
        uint32_t m_RendererID;
        uint32_t m_ColorAttachment;
        const FrameBufferSpecification& m_Specification;
    };

}
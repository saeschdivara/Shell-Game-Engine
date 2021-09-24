#pragma once

#include "Engine/Core/Rendering/Buffer.h"

namespace Shell {

    class OpenGLVertexBuffer : public VertexBuffer {
    public:
        OpenGLVertexBuffer(float * vertices, uint32_t size);
        virtual ~OpenGLVertexBuffer();

        void Bind() override;
        void Unbind() override;

    private:
        uint32_t m_RendererID;
    };

}


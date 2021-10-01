#include "OpenGLFrameBuffer.h"

#include <glad/glad.h>

namespace Shell {
    OpenGLFrameBuffer::OpenGLFrameBuffer(const FrameBufferSpecification &specification)
        : m_Specification(specification)
    {
        Recreate();
    }

    OpenGLFrameBuffer::~OpenGLFrameBuffer() {
        glDeleteFramebuffers(1, &m_RendererID);
    }

    void OpenGLFrameBuffer::Recreate() {
        glGenFramebuffers(1, &m_RendererID);

        glGenTextures(1, &m_ColorAttachment);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8)
    }

}

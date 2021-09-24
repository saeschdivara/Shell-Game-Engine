#include "OpenGLBuffer.h"

#include <glad/glad.h>

namespace Shell {
    OpenGLVertexBuffer::OpenGLVertexBuffer(float *vertices, uint32_t size) {
        glGenBuffers(1, &m_RendererID);
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);

        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer() {
        glDeleteBuffers(1, &m_RendererID);
    }

    void OpenGLVertexBuffer::Bind() {
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    }

    void OpenGLVertexBuffer::Unbind() {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}
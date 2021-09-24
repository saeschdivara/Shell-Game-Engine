#include "OpenGLBuffer.h"

#include <glad/glad.h>

namespace Shell {

    ///////////////////////////
    // VertexBuffer
    ///////////////////////////

    OpenGLVertexBuffer::OpenGLVertexBuffer(float *vertices, uint32_t size) : m_Layout() {
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

    ///////////////////////////
    // IndexBuffer
    ///////////////////////////

    OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t *vertices, uint32_t count) : m_VerticesCount(count) {
        glGenBuffers(1, &m_RendererID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * count, vertices, GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer() {
        glDeleteBuffers(1, &m_RendererID);
    }

    void OpenGLIndexBuffer::Bind() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    }

    void OpenGLIndexBuffer::Unbind() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}
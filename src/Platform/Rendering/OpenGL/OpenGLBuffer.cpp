#include "OpenGLBuffer.h"

#include "Engine/Core/Profiling.h"

#include <glad/glad.h>

namespace Shell {

    ///////////////////////////
    // VertexBuffer
    ///////////////////////////

    OpenGLVertexBuffer::OpenGLVertexBuffer(float *vertices, uint32_t size) : m_Layout() {
        OPTICK_EVENT();

        glGenBuffers(1, &m_RendererID);
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);

        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer() {
        OPTICK_EVENT();

        glDeleteBuffers(1, &m_RendererID);
    }

    void OpenGLVertexBuffer::Bind() {
        OPTICK_EVENT();

        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    }

    void OpenGLVertexBuffer::Unbind() {
        OPTICK_EVENT();

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    ///////////////////////////
    // IndexBuffer
    ///////////////////////////

    OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t *vertices, uint32_t count) : m_VerticesCount(count) {
        OPTICK_EVENT();

        glGenBuffers(1, &m_RendererID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * count, vertices, GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer() {
        OPTICK_EVENT();

        glDeleteBuffers(1, &m_RendererID);
    }

    void OpenGLIndexBuffer::Bind() {
        OPTICK_EVENT();

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    }

    void OpenGLIndexBuffer::Unbind() {
        OPTICK_EVENT();

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}
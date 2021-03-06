#include "OpenGLBufferContainer.h"

#include "Engine/Core/Profiling.h"

#include <glad/glad.h>

namespace Shell {

    static GLenum GetOpenGLTypeFromShaderDataType(ShaderDataType dataType) {
        OPTICK_EVENT();

        switch (dataType) {
            case ShaderDataType::Float: return GL_FLOAT;
            case ShaderDataType::Float2: return GL_FLOAT;
            case ShaderDataType::Float3: return GL_FLOAT;
            case ShaderDataType::Float4: return GL_FLOAT;

            case ShaderDataType::Mat3: return GL_FLOAT;
            case ShaderDataType::Mat4: return GL_FLOAT;

            case ShaderDataType::Int: return GL_INT;
            case ShaderDataType::Int2: return GL_INT;
            case ShaderDataType::Int3: return GL_INT;
            case ShaderDataType::Int4: return GL_INT;

            case ShaderDataType::Bool: return GL_BOOL;

            default:
                SHELL_CORE_ASSERT(false, "Unknown shader type was used")
                return 0;
        }
    }

    OpenGLBufferContainer::OpenGLBufferContainer() : m_RendererID(0) {
        OPTICK_EVENT();

        glGenVertexArrays(1, &m_RendererID);
    }

    OpenGLBufferContainer::~OpenGLBufferContainer() {
        OPTICK_EVENT();

        glDeleteVertexArrays(1, &m_RendererID);
    }

    void OpenGLBufferContainer::Bind() {
        OPTICK_EVENT();

        glBindVertexArray(m_RendererID);
    }

    void OpenGLBufferContainer::Unbind() {
        OPTICK_EVENT();

        glBindVertexArray(0);
    }

    void OpenGLBufferContainer::AddBuffer(const Ref<Buffer> buffer) {
        OPTICK_EVENT();

        glBindVertexArray(m_RendererID); // to make sure it is bound
        buffer->Bind();

        auto vertexPointer = dynamic_pointer_cast<VertexBuffer>(buffer);
        if (vertexPointer) {
            SHELL_CORE_ASSERT(vertexPointer->HasValidLayout(), "You vertex buffer needs to have a layout set");
            const auto& layout = vertexPointer->GetLayout();

            uint32_t index = 0;
            for (const auto &item: layout) {
                glEnableVertexAttribArray(index);
                glVertexAttribPointer(
                        index,
                        item.GetElementCount(),
                        GetOpenGLTypeFromShaderDataType(item.DataType),
                        item.Normalized ? GL_TRUE : GL_FALSE,
                        layout.GetStride(),
                        (void *)item.Offset
                );

                index += 1;
            }

            m_Buffers.push_back(buffer);
        }
        else {
            auto indexPointer = dynamic_pointer_cast<IndexBuffer>(buffer);
            SHELL_CORE_ASSERT(indexPointer, "Buffer is neither an vertex nor an index buffer")

            if (indexPointer) {
                SHELL_CORE_ASSERT(m_IndexBuffer == nullptr, "Currently only one index buffer is supported")
                m_IndexBuffer = indexPointer;
            }
        }
    }
}
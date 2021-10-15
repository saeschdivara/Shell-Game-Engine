#include "RenderQueue.h"

#include <utility>

#include "Engine/Core/Rendering/Renderer.h"

namespace Shell {
    static float texturedSquareVertices [] = {
            //x      y      z
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
            0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
    };

    void RenderQueue::Init() {
        /////////////// TEXTURED ///////////////
        m_BufferContainerWithTextures = BufferContainer::Create();

        auto textureVertexBuffer = VertexBuffer::Create(texturedSquareVertices, sizeof(texturedSquareVertices));

        BufferLayout layoutWithTexture = {
                { ShaderDataType::Float3, "a_Position" },
                { ShaderDataType::Float2, "a_TexCoord" },
        };

        textureVertexBuffer->SetLayout(layoutWithTexture);
        m_BufferContainerWithTextures->AddBuffer(textureVertexBuffer);

        uint32_t indices[] = { 0, 1, 2, 2, 3, 0 };
        auto indexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
        m_BufferContainerWithTextures->AddBuffer(indexBuffer);

        m_TexturedShader = Shader::CreateFromFiles(
                "assets/shaders/textured/vertex.glsl",
                "assets/shaders/textured/fragment.glsl"
        );

        m_TexturedShader->Bind();
        m_TexturedShader->SetUniform("u_Texture", 0);

        /////////////// FLAT COLOR ///////////////

        m_BufferContainerWithColors = BufferContainer::Create();

        auto colorVertexBuffer = VertexBuffer::Create(texturedSquareVertices, sizeof(texturedSquareVertices));

        BufferLayout layoutWithColor = {
                { ShaderDataType::Float3, "a_Position" },
                { ShaderDataType::Float4, "a_Color" },
        };

        colorVertexBuffer->SetLayout(layoutWithColor);
        m_BufferContainerWithColors->AddBuffer(colorVertexBuffer);

        m_BufferContainerWithColors->AddBuffer(indexBuffer);

        m_FlatColorShader = Shader::CreateFromFiles(
                "assets/shaders/flat-color/vertex.glsl",
                "assets/shaders/flat-color/fragment.glsl"
        );

        m_Data.Entries = new QueueEntry[MAX_NUM_INDICES];
    }

    void RenderQueue::EnqueueTexturedQuad(Ref <Texture2D> texture, glm::mat4 transform) {
        m_Data.CurrentEntry->Texture = std::move(texture);
        m_Data.CurrentEntry->Transform = transform;
        m_Data.CurrentEntry++;
    }

    void RenderQueue::EnqueueColoredQuad(glm::vec4 &color, glm::mat4 transform) {
        m_Data.CurrentEntry->Color = color;
        m_Data.CurrentEntry->Transform = transform;
        m_Data.CurrentEntry++;
    }

    void RenderQueue::StartBatch() {
        m_Data.CurrentEntry = m_Data.Entries;
    }

    void RenderQueue::Flush() {
        for (auto dataPtr = m_Data.Entries; dataPtr < m_Data.CurrentEntry; dataPtr++) {
            if (dataPtr->Texture) {
                dataPtr->Texture->Bind();
                Renderer::Instance()->Submit(m_BufferContainerWithTextures, m_TexturedShader, dataPtr->Transform);
            } else {
                m_FlatColorShader->Bind();
                m_FlatColorShader->SetUniform("a_Color", dataPtr->Color);

                Renderer::Instance()->Submit(m_BufferContainerWithColors, m_FlatColorShader, dataPtr->Transform);
            }
        }
    }
}
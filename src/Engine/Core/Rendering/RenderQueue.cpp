#include "RenderQueue.h"

#include "Engine/Core/Rendering/Renderer.h"

namespace Shell {
    void RenderQueue::Init() {
        m_BufferContainerWithTextures = BufferContainer::Create();

        float texturedSquareVertices [] = {
                //x      y      z
                -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
                0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
                0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
                -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
        };

        auto m_TextureVertexBuffer = VertexBuffer::Create(texturedSquareVertices, sizeof(texturedSquareVertices));

        BufferLayout layoutWithTexture = {
                { ShaderDataType::Float3, "a_Position" },
                { ShaderDataType::Float2, "a_TexCoord" },
        };

        m_TextureVertexBuffer->SetLayout(layoutWithTexture);
        m_BufferContainerWithTextures->AddBuffer(m_TextureVertexBuffer);

        uint32_t indices[] = { 0, 1, 2, 2, 3, 0 };
        auto indexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
        m_BufferContainerWithTextures->AddBuffer(indexBuffer);

        m_TexturedShader = Shader::CreateFromFiles(
                "assets/shaders/textured/vertex.glsl",
                "assets/shaders/textured/fragment.glsl"
        );

        m_TexturedShader->Bind();
        m_TexturedShader->SetUniform("u_Texture", 0);

        m_Data.Entries = new QueueEntry[MAX_NUM_INDICES];
    }

    void RenderQueue::EnqueueTexturedQuad(Ref <Texture2D> texture, glm::mat4 transform) {
        m_Data.CurrentEntry->Texture = texture;
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
            dataPtr->Texture->Bind();
            Renderer::Instance()->Submit(m_BufferContainerWithTextures, m_TexturedShader, dataPtr->Transform);
        }
    }
}
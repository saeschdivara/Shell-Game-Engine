#pragma once

#include "Engine/Core/Rendering/BufferContainer.h"
#include "Engine/Core/Rendering/Shader.h"
#include "Engine/Core/Rendering/Texture.h"
#include <glm/glm.hpp>

namespace Shell {

    const int MAX_NUM_INDICES = 40000;

    struct QueueEntry {
        glm::vec4 Color;
        Ref<Texture2D> Texture;

        glm::mat4 Transform;
    };

    struct QueueData {
        QueueEntry * Entries = nullptr;
        QueueEntry * CurrentEntry = nullptr;
    };

    class RenderQueue {
    public:
        void Init();

        void EnqueueTexturedQuad(Ref<Texture2D> texture, glm::mat4 transform);
        void EnqueueColoredQuad(glm::vec4 &color, glm::mat4 transform);

        void StartBatch();
        void Flush();

    private:
        QueueData m_Data;

        Ref<BufferContainer> m_BufferContainerWithTextures;
        Ref<Shader> m_TexturedShader;

        Ref<BufferContainer> m_BufferContainerWithColors;
        Ref<Shader> m_FlatColorShader;
    };
}

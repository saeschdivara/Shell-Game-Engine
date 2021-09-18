#pragma once

#include "Engine/Core/Utils.h"

#include <glad/glad.h>
#include <vector>

namespace Shell {

    struct RenderBatchUnit {
        GLuint vertexbuffer;
        GLuint programID;
    };

    class Renderer {
    public:
        static Scope<Renderer>& Instance();

        void AddBatch(RenderBatchUnit batch);
        void RenderBatch();

    private:
        static Scope<Renderer> Create();
        static Scope<Renderer> m_Instance;

        std::vector<RenderBatchUnit> m_Batches;
    };
}

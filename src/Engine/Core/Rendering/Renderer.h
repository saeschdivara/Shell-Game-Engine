#pragma once

#include "Engine/Core/Utils.h"
#include "Engine/Core/Rendering/API.h"
#include "Engine/Core/Rendering/BufferContainer.h"

#include <glm/glm.hpp>

namespace Shell {

    class Renderer {
    public:
        static Scope<Renderer>& Instance();

        void BeginScene();
        void EndScene();

        void Submit(const Ref<BufferContainer>& bufferContainer);

        RenderAPI getCurrentApi() const { return m_API; }

    private:
        static Scope<Renderer> Create();

    private:
        RenderAPI m_API;

        static Scope<Renderer> m_Instance;
    };
}

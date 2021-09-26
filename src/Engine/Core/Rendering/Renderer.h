#pragma once

#include "Engine/Core/Utils.h"
#include "Engine/Core/Rendering/API.h"
#include "Engine/Core/Rendering/Camera.h"
#include "Engine/Core/Rendering/BufferContainer.h"
#include "Engine/Core/Rendering/Shader.h"

#include <glm/glm.hpp>

namespace Shell {

    class Renderer {
    public:
        static Scope<Renderer>& Instance();

        void BeginScene(Ref<OrthographicCamera> camera);
        void EndScene();

        void Submit(const Ref<BufferContainer>& bufferContainer, const Ref<Shader>& shader, const glm::mat4 & transform = glm::mat4(1.0f));

        RenderAPI getCurrentApi() const { return m_API; }

    private:
        static Scope<Renderer> Create();

    private:
        RenderAPI m_API;
        Ref<OrthographicCamera> m_Camera;

        static Scope<Renderer> m_Instance;
    };
}

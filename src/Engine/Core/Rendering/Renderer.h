#pragma once

#include "Engine/Core/Utils.h"
#include "Engine/Core/Rendering/API.h"
#include "Engine/Core/Rendering/Camera.h"
#include "Engine/Core/Rendering/BufferContainer.h"
#include "Engine/Core/Rendering/Shader.h"

namespace Shell {

    class Renderer {
    public:
        static Scope<Renderer>& Instance();

        void BeginScene(Ref<OrthographicCamera> camera);
        void EndScene();

        void Submit(const Ref<BufferContainer>& bufferContainer, const Ref<Shader>& shader);

        RenderAPI getCurrentApi() const { return m_API; }

    private:
        static Scope<Renderer> Create();

    private:
        RenderAPI m_API;
        Ref<OrthographicCamera> m_Camera;

        static Scope<Renderer> m_Instance;
    };
}

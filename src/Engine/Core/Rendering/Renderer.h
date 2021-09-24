#pragma once

#include "Engine/Core/Utils.h"

#include "Engine/Core/Rendering/API.h"

namespace Shell {

    class Renderer {
    public:
        static Scope<Renderer>& Instance();

        RenderAPI getCurrentApi() const { return m_API; }

    private:
        static Scope<Renderer> Create();

    private:
        RenderAPI m_API;

        static Scope<Renderer> m_Instance;
    };
}

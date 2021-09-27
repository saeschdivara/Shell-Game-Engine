#include "Texture.h"

#include "Engine/Core/Rendering/Renderer.h"
#include "Platform/Rendering/OpenGL/OpenGLTexture.h"

namespace Shell {

    Ref<Texture2D> Texture2D::Create(const std::string & path) {
        switch (Renderer::Instance()->getCurrentApi()) {
            case RenderAPI::OpenGL:
                return CreateRef<OpenGLTexture2D>(path);

            default:
                SHELL_CORE_ASSERT(false, "Render API implementation not found");
                return {};
        }
    }
}
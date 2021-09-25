#pragma once

#include "Engine/Core/Rendering/Buffer.h"

namespace Shell {

    class BufferContainer {
    public:
        virtual ~BufferContainer() {}

        virtual void Bind() = 0;
        virtual void Unbind() = 0;
        virtual void AddBuffer(Ref<Buffer> buffer) = 0;

        static Ref<BufferContainer> Create();
    };

}



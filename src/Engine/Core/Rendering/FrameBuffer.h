#pragma once

#include "Engine/Core/shellpch.h"

namespace Shell {

    struct FrameBufferSpecification {
        uint32_t Width, Height;
        uint32_t Samples = 1;

        bool SwapChainTarget = false;
    };

    class FrameBuffer {
    public:
        virtual ~FrameBuffer() {}
        virtual FrameBufferSpecification& GetSpecification() const = 0;

        static Ref<FrameBuffer> Create(const FrameBufferSpecification& specification);
    };
}

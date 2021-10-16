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
        virtual FrameBufferSpecification& GetSpecification() = 0;
        [[nodiscard]] virtual uint32_t GetColorAttachment() const = 0;

        virtual void Bind() = 0;
        virtual void Resize(uint32_t width, uint32_t height) = 0;
        virtual void Unbind() = 0;

        static Ref<FrameBuffer> Create(const FrameBufferSpecification& specification);
    };
}

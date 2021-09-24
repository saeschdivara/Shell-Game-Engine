#pragma once
#include "Engine/Core/shellpch.h"
#include "Engine/Core/Utils.h"

namespace Shell {

    class Buffer {
    public:
        virtual ~Buffer() = default;

        virtual void Bind() = 0;
        virtual void Unbind() = 0;
    };

    class VertexBuffer : public Buffer {
    public:
        static Ref<VertexBuffer> Create(float * vertices, uint32_t size);
    };

    class IndexBuffer : public Buffer {
    public:
        static Ref<IndexBuffer> Create(float * vertices, uint32_t size);
    };

}
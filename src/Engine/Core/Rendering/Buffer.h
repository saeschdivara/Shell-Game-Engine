#pragma once
#include "Engine/Core/shellpch.h"
#include "Engine/Core/Utils.h"

namespace Shell {

    enum class ShaderDataType {
        None = 0,
        Float, Float2, Float3, Float4,
        Mat3, Mat4,
        Int, Int2, Int3, Int4,
        Bool
    };

    static uint32_t GetShaderDataTypeSize(ShaderDataType dataType) {
        switch (dataType) {
            case ShaderDataType::Float: return sizeof(float);
            case ShaderDataType::Float2: return sizeof(float) * 2;
            case ShaderDataType::Float3: return sizeof(float) * 3;
            case ShaderDataType::Float4: return sizeof(float) * 4;

            case ShaderDataType::Mat3: return 4 * 3 * 3;
            case ShaderDataType::Mat4: return 4 * 4 * 4;

            case ShaderDataType::Int: return sizeof(uint32_t);
            case ShaderDataType::Int2: return sizeof(uint32_t) * 2;
            case ShaderDataType::Int3: return sizeof(uint32_t) * 3;
            case ShaderDataType::Int4: return sizeof(uint32_t) * 4;

            case ShaderDataType::Bool: return sizeof(bool);

            default:
            case ShaderDataType::None:
                SHELL_CORE_ASSERT(false, "Unknown shader type was used")
                return 0;
        }
    }

    struct BufferElement {
        std::string Name;
        ShaderDataType DataType;
        bool Normalized;
        uint32_t Offset;
        uint32_t Size;

        BufferElement(ShaderDataType dataType, const std::string& name)
            : Name(name), DataType(dataType), Normalized(false), Size(GetShaderDataTypeSize(dataType)), Offset(0) {}

        [[nodiscard]] uint32_t GetElementCount() const {
            switch (DataType) {
                case ShaderDataType::Float: return 1;
                case ShaderDataType::Float2: return 2;
                case ShaderDataType::Float3: return 3;
                case ShaderDataType::Float4: return 4;

                case ShaderDataType::Mat3: return 3 * 3;
                case ShaderDataType::Mat4: return 4 * 4;

                case ShaderDataType::Int: return 1;
                case ShaderDataType::Int2: return 2;
                case ShaderDataType::Int3: return 3;
                case ShaderDataType::Int4: return 4;

                case ShaderDataType::Bool: return 1;

                default:
                case ShaderDataType::None:
                SHELL_CORE_ASSERT(false, "Unknown shader type was used")
                    return 0;
            }
        }
    };

    class BufferLayout {
    public:
        BufferLayout() = default;

        BufferLayout(const std::initializer_list<BufferElement>& elements) : m_Elements(elements) {
            CalculateOffsetAndStride();
        }

        [[nodiscard]] inline uint32_t GetStride() const { return m_Stride; }
        [[nodiscard]] inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }

        std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
        std::vector<BufferElement>::iterator end() { return m_Elements.end(); }

    private:
        void CalculateOffsetAndStride() {
            uint32_t offset = 0;
            m_Stride = 0;

            for (auto &element: m_Elements) {
                element.Offset = offset;
                offset += element.Size;
                m_Stride += element.Size;
            }
        }

    private:
        std::vector<BufferElement> m_Elements;
        uint32_t m_Stride = 0;
    };

    class Buffer {
    public:
        virtual ~Buffer() = default;

        virtual void Bind() = 0;
        virtual void Unbind() = 0;
    };

    class VertexBuffer : public Buffer {
    public:
        virtual void SetLayout(const BufferLayout& layout) = 0;
        [[nodiscard]] virtual BufferLayout GetLayout() const = 0;

        static Ref<VertexBuffer> Create(float * vertices, uint32_t size);
    };

    class IndexBuffer : public Buffer {
    public:

        [[nodiscard]] virtual uint32_t GetCount() const = 0;

        static Ref<IndexBuffer> Create(uint32_t * vertices, uint32_t count);
    };

}
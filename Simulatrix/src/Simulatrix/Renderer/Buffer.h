#pragma once
#include <Simulatrix/Core/Core.h>


namespace Simulatrix {
    enum class ShaderDataType {
        None = 0, Float, Vec2, Vec3, Vec4, Mat3, Mat4, Int, IVec2, IVec3, Bool
    };

    static uint32_t ShaderDataTypeSize(ShaderDataType type) {
        switch (type) {
            case ShaderDataType::Float: return 4;
            case ShaderDataType::Vec2:  return 4 * 2;
            case ShaderDataType::Vec3:  return 4 * 3;
            case ShaderDataType::Vec4:  return 4 * 4;
            case ShaderDataType::Mat3:  return 4 * 3 * 3;
            case ShaderDataType::Mat4:  return 4 * 4 * 4;
            case ShaderDataType::Int:   return 4;
            case ShaderDataType::IVec2: return 4 * 2;
            case ShaderDataType::IVec3: return 4 * 3;
            case ShaderDataType::Bool:  return 1;
        }
        SIMIX_CORE_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }

    struct BufferElement {
        std::string Name;
        ShaderDataType Type;
        uint32_t Offset, Size;
        bool Normalized;

        BufferElement(){}

        BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
            : Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
        {

        }

        uint32_t GetComponentCount() const {
            switch (Type) {
                case ShaderDataType::Float: return 1;
                case ShaderDataType::Vec2:  return 2;
                case ShaderDataType::Vec3:  return 3;
                case ShaderDataType::Vec4:  return 4;
                case ShaderDataType::Mat3:  return 3 * 3;
                case ShaderDataType::Mat4:  return 4 * 4;
                case ShaderDataType::Int:   return 1;
                case ShaderDataType::IVec2: return 2;
                case ShaderDataType::IVec3: return 3;
                case ShaderDataType::Bool:  return 1;
            }
            SIMIX_CORE_ASSERT(false, "Unknown ShaderDataType!");
            return 0;
        }
    };

    class BufferLayout {
    public:
        BufferLayout(){}

        BufferLayout(const std::initializer_list<BufferElement>& elements) : m_Elements(elements) {
            CalculateOffsetsAndStride();
        }
        inline uint32_t GetStride() const { return m_Stride; };
        inline const std::vector<BufferElement>& GetElements() const { return m_Elements; };
        

        std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
        std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
        std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
        std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
    private:
        void CalculateOffsetsAndStride() {
            uint32_t offset = 0;
            m_Stride = 0;
            for (auto& element : m_Elements) {
                element.Offset = offset;
                offset += element.Size;
                m_Stride += element.Size;
            }
        }
    private:
        std::vector<BufferElement> m_Elements;
        uint32_t m_Stride;
    };

    class VertexBuffer {
    public:
        virtual ~VertexBuffer(){}

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void SetLayout(const BufferLayout& layout) = 0;
        virtual const BufferLayout& GetLayout() const = 0;

        static VertexBuffer* Create(float* vertices, uint32_t size);
    };

    class IndexBuffer {
    public:
        virtual ~IndexBuffer() {}

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual uint32_t GetCount() const = 0;

        static IndexBuffer* Create(uint32_t* indices, uint32_t size);
    };
}
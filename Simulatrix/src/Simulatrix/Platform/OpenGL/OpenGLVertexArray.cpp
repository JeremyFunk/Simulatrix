#include <simixpch.h>
#include "OpenGLVertexArray.h"
#include <glad/glad.h>
namespace Simulatrix {

    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
        switch (type) {
            case ShaderDataType::Float: return GL_FLOAT;
            case ShaderDataType::Vec2:  return GL_FLOAT;
            case ShaderDataType::Vec3:  return GL_FLOAT;
            case ShaderDataType::Vec4:  return GL_FLOAT;
            case ShaderDataType::Mat3:  return GL_FLOAT;
            case ShaderDataType::Mat4:  return GL_FLOAT;
            case ShaderDataType::Int:   return GL_INT;
            case ShaderDataType::IVec2: return GL_INT;
            case ShaderDataType::IVec3: return GL_INT;
            case ShaderDataType::Bool:  return GL_BOOL;
        }
        SIMIX_CORE_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }

    OpenGLVertexArray::OpenGLVertexArray() {
        glCreateVertexArrays(1, &m_RendererID);
    }
    void OpenGLVertexArray::Bind() const
    {
        glBindVertexArray(m_RendererID);
    }
    void OpenGLVertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }
    void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
    {
        SIMIX_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex buffer has no layout!");

        glBindVertexArray(m_RendererID);
        vertexBuffer->Bind();

        uint32_t index = 0;
        const auto& layout = vertexBuffer->GetLayout();
        for (auto const& element : layout) {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(
                index,
                element.GetComponentCount(),
                ShaderDataTypeToOpenGLBaseType(element.Type),
                element.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(),
                (const void*)element.Offset
            );

            index++;
        }

        m_VertexBuffers.push_back(vertexBuffer);
    }
    void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
    {
        glBindVertexArray(m_RendererID);
        indexBuffer->Bind();
        m_IndexBuffer = indexBuffer;
    }
    const Ref<IndexBuffer>& OpenGLVertexArray::GetIndexBuffer()
    {
        return m_IndexBuffer;
    }
}
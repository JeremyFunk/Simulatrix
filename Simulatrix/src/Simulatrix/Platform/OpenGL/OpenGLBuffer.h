#pragma once
#include "Simulatrix/Renderer/Buffer.h"
#include "Simulatrix/ResourceManager/ResourceData.h"
namespace Simulatrix {
    class OpenGLVertexBuffer : public VertexBuffer {
    public:
        OpenGLVertexBuffer(float* vertices, uint32_t size);
        OpenGLVertexBuffer(std::vector<ResourceVertex> vertices);
        virtual ~OpenGLVertexBuffer();

        virtual void Bind() const override;
        virtual void Unbind() const override;


        virtual void SetLayout(const BufferLayout& layout) { m_Layout = layout; };
        virtual const BufferLayout& GetLayout() const { return m_Layout; }
    private:
        uint32_t m_RendererID;
        BufferLayout m_Layout;
    };
    class OpenGLIndexBuffer : public IndexBuffer {
    public:
        OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
        OpenGLIndexBuffer(std::vector<uint32_t> indices);
        virtual ~OpenGLIndexBuffer();

        virtual uint32_t GetCount() const override;

        virtual void Bind() const override;
        virtual void Unbind() const override;
    private:
        uint32_t m_RendererID;
        uint32_t m_Count;
    };
}
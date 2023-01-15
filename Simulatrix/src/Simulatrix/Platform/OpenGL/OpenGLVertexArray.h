#pragma once

#include "Simulatrix/Renderer/Buffer.h"
#include "Simulatrix/Renderer/VertexArray.h"

namespace Simulatrix {
    class OpenGLVertexArray : public VertexArray {
    public:
        OpenGLVertexArray();
        virtual ~OpenGLVertexArray() {}

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
        virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;
        virtual const Ref<IndexBuffer>& GetIndexBuffer() override;
    private:
        std::vector<Ref<VertexBuffer>> m_VertexBuffers;
        Ref<IndexBuffer> m_IndexBuffer;
        uint32_t m_RendererID;
    };
}
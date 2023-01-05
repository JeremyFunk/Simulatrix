#include "simixpch.h"
#include "Buffer.h"
#include "Simulatrix/Renderer/Renderer.h"
#include <Simulatrix/Core/Core.h>

#include "Simulatrix/Platform/OpenGL/OpenGLBuffer.h"

namespace Simulatrix {
    VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size) {
        switch (Renderer::GetAPI()) {
        case RendererAPI::API::None: SIMIX_CORE_ASSERT(false, "RendererAPI::None is not supported!");
        case RendererAPI::API::OpenGL: return new OpenGLVertexBuffer(vertices, size);
        }
        SIMIX_CORE_ASSERT(false, "Unknown renderer API!");
    }
    IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size) {
        switch (Renderer::GetAPI()) {
        case RendererAPI::API::None: SIMIX_CORE_ASSERT(false, "RendererAPI::None is not supported!");
        case RendererAPI::API::OpenGL: return new OpenGLIndexBuffer(indices, size);
        }
        SIMIX_CORE_ASSERT(false, "Unknown renderer API!");
    }
}
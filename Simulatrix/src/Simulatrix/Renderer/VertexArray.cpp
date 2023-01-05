#pragma once
#include <simixpch.h>
#include "Renderer.h"
#include "VertexArray.h"
#include "Simulatrix/Platform/OpenGL/OpenGLVertexArray.h"
namespace Simulatrix {
    VertexArray* VertexArray::Create()
    {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None: SIMIX_CORE_ASSERT(false, "RendererAPI::None is not supported!");
            case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
        }
        SIMIX_CORE_ASSERT(false, "Unknown renderer API!");
    }
}
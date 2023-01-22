#include "simixpch.h"
#include "Shader.h"
#include <Simulatrix/Debug/Log.h>
#include "Renderer.h"
#include "Simulatrix/Platform/OpenGL/OpenGLShader.h"
namespace Simulatrix {
    Shader* Shader::Create(std::string& vertexSrc, std::string& fragmentSrc)
    {
        switch (Renderer::GetAPI()) {
        case RendererAPI::API::None: SIMIX_CORE_ASSERT(false, "RendererAPI::None is not supported!");
        case RendererAPI::API::OpenGL: return new OpenGLShader(vertexSrc, fragmentSrc);
        }
        SIMIX_CORE_ASSERT(false, "Unknown renderer API!");
    }
    Shader* Shader::Create(Path& path)
    {
        switch (Renderer::GetAPI()) {
        case RendererAPI::API::None: SIMIX_CORE_ASSERT(false, "RendererAPI::None is not supported!");
        case RendererAPI::API::OpenGL: return new OpenGLShader(path);
        }
        SIMIX_CORE_ASSERT(false, "Unknown renderer API!");
    }
}
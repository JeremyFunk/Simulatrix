#include <simixpch.h>
#include "RenderCommand.h"
#include "Simulatrix/Platform/OpenGL/OpenGLRendererAPI.h"
namespace Simulatrix {
    RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}
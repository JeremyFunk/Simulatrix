#include "simixpch.h"
#include "Framebuffer.h"
#include "Simulatrix/Renderer/Renderer.h"
#include "Simulatrix/Platform/OpenGL/OpenGLFramebuffer.h"

namespace Simulatrix {
	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    SIMIX_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLFramebuffer>(spec);
		}

		SIMIX_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
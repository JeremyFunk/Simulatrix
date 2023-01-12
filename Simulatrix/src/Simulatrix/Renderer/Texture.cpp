#include "simixpch.h"
#include "Texture.h"
#include "Simulatrix/Core/Core.h"
#include "Simulatrix/Renderer/Renderer.h"
#include "Simulatrix/Platform/OpenGL/OpenGLTexture2D.h"

namespace Simulatrix {
	Texture2D* Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    SIMIX_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return new OpenGLTexture2D(width, height);
		}

		SIMIX_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Texture2D* Texture2D::Create(const Path& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    SIMIX_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return new OpenGLTexture2D(path);
		}

		SIMIX_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
#include "simixpch.h"
#include "Pipeline.h"
#include "Simulatrix/Renderer/Renderer.h"
#include "Simulatrix/Platform/OpenGL/OpenGLPipeline.h"

namespace Simulatrix {
	Ref<Pipeline> Pipeline::Create(const PipelineSpecification& spec)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    SIMIX_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLPipeline>(spec);
		}

		SIMIX_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
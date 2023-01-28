#pragma once
#include "Shader.h"
#include "Framebuffer.h"

namespace Simulatrix {
	struct PipelineSpecification
	{
		Ref<Shader> Shader;
		Ref<Framebuffer> Framebuffer;
		bool BackfaceCulling = true;
		bool DepthTest = true;
		bool DepthWrite = true;
		bool Wireframe = false;
		float LineWidth = 1.0f;

		std::string DebugName;
	};

    class Pipeline {
	public:
		virtual ~Pipeline() = default;

		virtual PipelineSpecification& GetSpecification() = 0;
		virtual const PipelineSpecification& GetSpecification() const = 0;

		virtual void Invalidate() = 0;
		//virtual void SetUniformBuffer(Ref<UniformBuffer> uniformBuffer, uint32_t binding, uint32_t set = 0) = 0;
        virtual Ref<Shader> GetShader() = 0;

		virtual void Bind() = 0;
		virtual UUID GetID() const = 0;

		static Ref<Pipeline> Create(const PipelineSpecification& spec);
    };
}
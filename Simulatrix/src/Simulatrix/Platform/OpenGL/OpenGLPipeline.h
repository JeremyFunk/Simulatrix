#pragma once
#include "Simulatrix/Renderer/Pipeline.h"

namespace Simulatrix {
	class OpenGLPipeline : public Pipeline {
	public:
		virtual ~OpenGLPipeline() {
			
		}
		OpenGLPipeline(const PipelineSpecification& spec) : m_Specs(spec) {}
		virtual PipelineSpecification& GetSpecification() override {
			return m_Specs;
		}
		virtual const PipelineSpecification& GetSpecification() const override {
			return m_Specs;
		}

        virtual Ref<Shader> GetShader() override {
            return m_Specs.Shader;
        }

		virtual void Invalidate() override;
		virtual void Bind() override;
        virtual UUID GetID() const override {
            return m_UUID;
        }
	private:
		PipelineSpecification m_Specs;
		UUID m_UUID;
    };
}


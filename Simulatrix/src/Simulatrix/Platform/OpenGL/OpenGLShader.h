#pragma once
#include <string>
#include <Simulatrix/Renderer/Shader.h>

namespace Simulatrix {
    class OpenGLShader : public Shader {
    public:
        OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
        ~OpenGLShader();

        virtual void Bind() const override;
        virtual void Unbind() const override;
        virtual void AddUniform(ShaderUniform uniform) override;
        virtual void AddUniforms(ShaderUniforms uniforms) override;
        virtual void SetUniform(uint32_t rendererID, float value) override;
        virtual void SetUniform(const char* name, float value) override;
        virtual void SetUniform(uint32_t rendererID, const glm::mat4& value) override;
        virtual void SetUniform(const char* name, const glm::mat4& value) override;
        virtual const ShaderUniforms& GetUniforms() const override;
    private:
        uint32_t m_RendererID;
        ShaderUniforms m_Uniforms;
    };
}
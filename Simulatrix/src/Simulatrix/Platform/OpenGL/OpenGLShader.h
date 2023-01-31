#pragma once
#include <string>
#include <Simulatrix/Renderer/Shader.h>
#include <Simulatrix/Core/IOWrapper.h>
#include <Simulatrix/Core/Core.h>


namespace Simulatrix {
    class OpenGLShader : public Shader {
    public:
        OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
        OpenGLShader(Path& path);
        ~OpenGLShader();

        virtual void Bind() const override;
        virtual void Unbind() const override;
        virtual void AddUniform(ShaderUniform uniform) override;
        virtual void AddUniforms(ShaderUniforms uniforms) override;
        virtual void SetUniform(uint32_t rendererID, float value) override;
        virtual void SetUniform(uint32_t rendererID, uint32_t value) override;
        virtual void SetUniform(uint32_t rendererID, int value) override;
        virtual void SetUniform(uint32_t rendererID, bool value) override;
        virtual void SetUniform(uint32_t rendererID, const glm::mat3& value) override;
        virtual void SetUniform(uint32_t rendererID, const glm::mat4& value) override;
        virtual void SetUniform(uint32_t rendererID, const glm::vec2& value) override;
        virtual void SetUniform(uint32_t rendererID, const glm::vec3& value) override;
        virtual void SetUniform(uint32_t rendererID, const glm::vec4& value) override;
        virtual void SetUniform(uint32_t rendererID, const glm::ivec2& value) override;
        virtual void SetUniform(uint32_t rendererID, const glm::ivec3& value) override;
        virtual void SetUniform(uint32_t rendererID, const glm::ivec4& value) override;
        virtual void SetUniform(const char* name, float value) override;
        virtual void SetUniform(const char* name, uint32_t value) override;
        virtual void SetUniform(const char* name, int value) override;
        virtual void SetUniform(const char* name, bool value) override;
        virtual void SetUniform(const char* name, const glm::mat3& value) override;
        virtual void SetUniform(const char* name, const glm::mat4& value) override;
        virtual void SetUniform(const char* name, const glm::vec2& value) override;
        virtual void SetUniform(const char* name, const glm::vec3& value) override;
        virtual void SetUniform(const char* name, const glm::vec4& value) override;
        virtual void SetUniform(const char* name, const glm::ivec2& value) override;
        virtual void SetUniform(const char* name, const glm::ivec3& value) override;
        virtual void SetUniform(const char* name, const glm::ivec4& value) override;
        virtual void Reload(std::string& vertexSrc, std::string& fragmentSrc) override;
        virtual void Reload(Path& path) override;

        virtual Path GetPath() override {
            return m_Path;
        }
        virtual UUID GetID() override {
            return m_ID;
        }
        virtual void SetID(UUID uuid) override {
            m_ID = uuid;
        }
        
        virtual void SetName(std::string name) {
            m_Name = name;
        }
        virtual std::string GetName() const {
            return m_Name;
        }

        virtual const ShaderUniforms& GetUniforms() const override;
    private:
        void Compile(std::string vertexSrc, std::string fragmentSrc);
        void ReadFromFile(Path& path);
    private:
        std::string m_Name = "Shader";
        uint32_t m_RendererID;
        UUID m_ID;
        ShaderUniforms m_Uniforms;
        Path m_Path;
    };
}
#pragma once
#include <string>
#include <Simulatrix/Renderer/Buffer.h>
#include <Simulatrix/Core/IOWrapper.h>
#include <Simulatrix/Core/Core.h>

namespace Simulatrix {
    struct ShaderUniform {
        std::string Name;
        ShaderDataType Type;
        uint32_t RendererID;
        ShaderUniform() {}

        ShaderUniform(ShaderDataType type, const std::string& name)
            : Name(name), Type(type)
        {

        }
    };

    class ShaderUniforms {
    public:
        ShaderUniforms() {}

        ShaderUniforms(const std::initializer_list<ShaderUniform>& elements) 
            : m_Elements(elements) {

        }
        inline const std::vector<ShaderUniform>& GetElements() const { return m_Elements; };

        void push_back(ShaderUniform& s) { m_Elements.push_back(s); }
        std::vector<ShaderUniform>::iterator begin() { return m_Elements.begin(); }
        std::vector<ShaderUniform>::iterator end() { return m_Elements.end(); }
        std::vector<ShaderUniform>::const_iterator begin() const { return m_Elements.begin(); }
        std::vector<ShaderUniform>::const_iterator end() const { return m_Elements.end(); }
    private:
        std::vector<ShaderUniform> m_Elements;
    };

    class Shader {
    public:
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
        virtual void SetName(std::string name) = 0;
        virtual std::string GetName() const = 0;
        virtual void AddUniform(ShaderUniform uniform) = 0;
        virtual void AddUniforms(ShaderUniforms uniforms) = 0;
        virtual void SetUniform(uint32_t rendererID, float value) = 0;
        virtual void SetUniform(uint32_t rendererID, uint32_t value) = 0;
        virtual void SetUniform(const char* name, float value) = 0;
        virtual void SetUniform(uint32_t rendererID, const glm::mat4& value) = 0;
        virtual void SetUniform(const char* name, const glm::mat4& value) = 0;
        virtual void Reload(std::string& vertexSrc, std::string& fragmentSrc) = 0;
        virtual void Reload(Path& path) = 0;
        virtual Path GetPath() = 0;
        virtual UUID GetID() = 0;
        virtual void SetID(UUID uuid) = 0;
        virtual const ShaderUniforms& GetUniforms() const = 0;
        static Shader* Create(std::string& vertexSrc, std::string& fragmentSrc);
        static Shader* Create(Path& path);
    };
}
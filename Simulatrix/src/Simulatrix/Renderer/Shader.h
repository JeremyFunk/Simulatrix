#pragma once
#include <string>
#include <Simulatrix/Renderer/Buffer.h>

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

        std::vector<ShaderUniform>::iterator begin() { return m_Elements.begin(); }
        std::vector<ShaderUniform>::iterator end() { return m_Elements.end(); }
        std::vector<ShaderUniform>::const_iterator begin() const { return m_Elements.begin(); }
        std::vector<ShaderUniform>::const_iterator end() const { return m_Elements.end(); }
    private:
        std::vector<ShaderUniform> m_Elements;
    };

    class Shader {
    public:
        Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
        ~Shader();

        void Bind() const;
        void Unbind() const;
        virtual void SetUniforms(ShaderUniforms& uniforms);
        const ShaderUniforms& GetUniforms() const;
    private:
        uint32_t m_RendererID;
        ShaderUniforms m_Uniforms;
    };
}
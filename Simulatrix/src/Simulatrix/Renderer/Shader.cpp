#include "simixpch.h"
#include "Shader.h"
#include <glad/glad.h>
#include <Simulatrix/Debug/Log.h>
namespace Simulatrix {
    Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        GLint Result = GL_FALSE;
        int InfoLogLength;

        GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
        GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

        // Compile Vertex Shader
        char const* VertexSourcePointer = vertexSrc.c_str();
        glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
        glCompileShader(VertexShaderID);

        // Check Vertex Shader
        glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
        glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if (InfoLogLength > 0) {
            std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
            glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
            SIMIX_CORE_ERROR("{0}", VertexShaderErrorMessage.data());
            SIMIX_CORE_ASSERT(false, "Vertex shader could not compile!");
            glDeleteShader(VertexShaderID);
            return;
        }



        // Compile Fragment Shader
        char const* FragmentSourcePointer = fragmentSrc.c_str();
        glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
        glCompileShader(FragmentShaderID);

        // Check Fragment Shader
        glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
        glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if (InfoLogLength > 0) {
            std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
            glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
            printf("%s\n", &FragmentShaderErrorMessage[0]);
            SIMIX_CORE_ERROR("{0}", FragmentShaderErrorMessage.data());
            SIMIX_CORE_ASSERT(false, "Fragment shader could not compile!");
            glDeleteShader(VertexShaderID);
            glDeleteShader(FragmentShaderID);
            return;
        }

        m_RendererID = glCreateProgram();
        glAttachShader(m_RendererID, VertexShaderID);
        glAttachShader(m_RendererID, FragmentShaderID);
        glLinkProgram(m_RendererID);

        glGetProgramiv(m_RendererID, GL_LINK_STATUS, &Result);
        glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if (InfoLogLength > 0) {
            std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
            glGetProgramInfoLog(m_RendererID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
            SIMIX_CORE_ERROR("{0}", ProgramErrorMessage.data());
            SIMIX_CORE_ASSERT(false, "Could not link program!");
        }


        glDetachShader(m_RendererID, VertexShaderID);
        glDetachShader(m_RendererID, FragmentShaderID);

        glDeleteShader(VertexShaderID);
        glDeleteShader(FragmentShaderID);
    }
    Shader::~Shader()
    {
        glDeleteProgram(m_RendererID);
    }
    void Shader::Bind() const
    {
        glUseProgram(m_RendererID);
    }
    void Shader::Unbind() const
    {
        glUseProgram(0);
    }
    void Shader::SetUniforms(ShaderUniforms& uniform)
    {
        m_Uniforms = uniform;
        for (auto& uniform : uniform) {
            uniform.RendererID = glGetUniformLocation(m_RendererID, uniform.Name.c_str());
        }
    }
    const ShaderUniforms& Shader::GetUniforms() const
    {
        return m_Uniforms;
    }
}
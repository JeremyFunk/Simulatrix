#include "simixpch.h"
#include "OpenGLShader.h"
#include <glad/glad.h>
#include <Simulatrix/Debug/Log.h>
#include <Simulatrix/ResourceManager/ResourceManager.h>
#include <Simulatrix/Util/StringUtil.h>
namespace Simulatrix {
    OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc) : m_Path(Path())
    {
        Compile(vertexSrc, fragmentSrc);
    }

    OpenGLShader::OpenGLShader(Path& path) : m_Path(path) {
        ReadFromFile(path);
    }
    void OpenGLShader::ReadFromFile(Path& path) {
        auto lines = ResourceManager::GetIO()->ReadTextLines(path);

        std::string vertexSrc = "";
        std::string fragmentSrc = "";

        int mode = 0; // 0 = None, 1 = VS, 2 = FS

        ShaderUniforms uniforms;

        for (auto line : lines) {
            auto trimmed = trim_copy(line);

            if (trimmed == "#VS") {
                mode = 1;
            }
            else if (trimmed == "#FS") {
                mode = 2;
            }
            else {
                if (mode == 1) {
                    vertexSrc += line + "\n";
                }
                else {
                    fragmentSrc += line + "\n";
                }

                if (trimmed.rfind("uniform", 0) == 0) {
                    auto split = Split(trimmed, ' ');
                    auto name = split[2].substr(0, split[2].size() - 1);
                    if (split[1] == "vec2")
                        uniforms.push_back(ShaderUniform(ShaderDataType::Vec2, name));
                    else if (split[1] == "vec3")
                        uniforms.push_back(ShaderUniform(ShaderDataType::Vec3, name));
                    else if (split[1] == "vec4")
                        uniforms.push_back(ShaderUniform(ShaderDataType::Vec4, name));

                    else if (split[1] == "mat3")
                        uniforms.push_back(ShaderUniform(ShaderDataType::Mat3, name));
                    else if (split[1] == "mat4")
                        uniforms.push_back(ShaderUniform(ShaderDataType::Mat4, name));

                    else if (split[1] == "float")
                        uniforms.push_back(ShaderUniform(ShaderDataType::Float, name));
                    else if (split[1] == "int" || split[1] == "sampler2D")
                        uniforms.push_back(ShaderUniform(ShaderDataType::Int, name));
                }
            }
        }

        Compile(vertexSrc, fragmentSrc);
        Bind();
        AddUniforms(uniforms);
    }

    void OpenGLShader::Reload(std::string& vertexSrc, std::string& fragmentSrc) {
        glDeleteProgram(m_RendererID);
        Compile(vertexSrc, fragmentSrc);
    }
    void OpenGLShader::Reload(Path& path) {
        glDeleteProgram(m_RendererID);
        ReadFromFile(path);
    }

    void OpenGLShader::Compile(std::string vertexSrc, std::string fragmentSrc) {
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

    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(m_RendererID);
    }
    void OpenGLShader::Bind() const
    {
        glUseProgram(m_RendererID);
    }
    void OpenGLShader::Unbind() const
    {
        glUseProgram(0);
    }
    void OpenGLShader::AddUniform(ShaderUniform uniform)
    {
        uniform.RendererID = glGetUniformLocation(m_RendererID, uniform.Name.c_str());
        m_Uniforms.push_back(uniform);
    }
    void OpenGLShader::AddUniforms(ShaderUniforms uniforms)
    {
        for (auto uniform : uniforms) {
            AddUniform(uniform);
        }
    }



    void OpenGLShader::SetUniform(uint32_t rendererID, float value) {
        glUniform1f(rendererID, value);
    }
    void OpenGLShader::SetUniform(uint32_t rendererID, uint32_t value) {
        glUniform1ui(rendererID, value);
    }
    void OpenGLShader::SetUniform(uint32_t rendererID, int value) {
        glUniform1i(rendererID, value);
    }
    void OpenGLShader::SetUniform(uint32_t rendererID, bool value) {
        glUniform1i(rendererID, value);
    }
    void OpenGLShader::SetUniform(uint32_t rendererID, const glm::mat3& value) {
        glUniformMatrix3fv(rendererID, 1, GL_FALSE, &value[0][0]);
    }
    void OpenGLShader::SetUniform(uint32_t rendererID, const glm::mat4& value) {
        glUniformMatrix4fv(rendererID, 1, GL_FALSE, &value[0][0]);
    }
    void OpenGLShader::SetUniform(uint32_t rendererID, const glm::vec2& value) {
        glUniform2f(rendererID, value.x, value.y);
    }
    void OpenGLShader::SetUniform(uint32_t rendererID, const glm::vec3& value) {
        glUniform3f(rendererID, value.x, value.y, value.z);
    }
    void OpenGLShader::SetUniform(uint32_t rendererID, const glm::vec4& value) {
        glUniform4f(rendererID, value.x, value.y, value.z, value.w);
    }
    void OpenGLShader::SetUniform(uint32_t rendererID, const glm::ivec2& value) {
        glUniform2i(rendererID, value.x, value.y);
    }
    void OpenGLShader::SetUniform(uint32_t rendererID, const glm::ivec3& value) {
        glUniform3i(rendererID, value.x, value.y, value.z);
    }
    void OpenGLShader::SetUniform(uint32_t rendererID, const glm::ivec4& value) {
        glUniform4i(rendererID, value.x, value.y, value.z, value.w);
    }





    void OpenGLShader::SetUniform(const char* name, float value) {
        for (const auto& uniform : m_Uniforms) {
            if (uniform.Name == name) {
                glUniform1f(uniform.RendererID, value);
            }
        }
    }
    void OpenGLShader::SetUniform(const char* name, uint32_t value) {
        for (const auto& uniform : m_Uniforms) {
            if (uniform.Name == name) {
                glUniform1ui(uniform.RendererID, value);
            }
        }
    }
    void OpenGLShader::SetUniform(const char* name, int value) {
        for (const auto& uniform : m_Uniforms) {
            if (uniform.Name == name) {
                glUniform1i(uniform.RendererID, value);
            }
        }
    }
    void OpenGLShader::SetUniform(const char* name, bool value) {
        for (const auto& uniform : m_Uniforms) {
            if (uniform.Name == name) {
                glUniform1i(uniform.RendererID, value);
            }
        }
    }
    void OpenGLShader::SetUniform(const char* name, const glm::mat3& value) {
        for (const auto& uniform : m_Uniforms) {
            if (uniform.Name == name) {
                glUniformMatrix3fv(uniform.RendererID, 1, GL_FALSE, &value[0][0]);
            }
        }
    }
    void OpenGLShader::SetUniform(const char* name, const glm::mat4& value) {
        for (const auto& uniform : m_Uniforms) {
            if (uniform.Name == name) {
                glUniformMatrix4fv(uniform.RendererID, 1, GL_FALSE, &value[0][0]);
            }
        }
    }
    void OpenGLShader::SetUniform(const char* name, const glm::vec2& value) {
        for (const auto& uniform : m_Uniforms) {
            if (uniform.Name == name) {
                glUniform2f(uniform.RendererID, value.x, value.y);
            }
        }
    }
    void OpenGLShader::SetUniform(const char* name, const glm::vec3& value) {
        for (const auto& uniform : m_Uniforms) {
            if (uniform.Name == name) {
                glUniform3f(uniform.RendererID, value.x, value.y, value.z);
            }
        }
    }
    void OpenGLShader::SetUniform(const char* name, const glm::vec4& value) {
        for (const auto& uniform : m_Uniforms) {
            if (uniform.Name == name) {
                glUniform4f(uniform.RendererID, value.x, value.y, value.z, value.w);
            }
        }
    }
    void OpenGLShader::SetUniform(const char* name, const glm::ivec2& value) {
        for (const auto& uniform : m_Uniforms) {
            if (uniform.Name == name) {
                glUniform2i(uniform.RendererID, value.x, value.y);
            }
        }
    }
    void OpenGLShader::SetUniform(const char* name, const glm::ivec3& value) {
        for (const auto& uniform : m_Uniforms) {
            if (uniform.Name == name) {
                glUniform3i(uniform.RendererID, value.x, value.y, value.z);
            }
        }
    }
    void OpenGLShader::SetUniform(const char* name, const glm::ivec4& value) {
        for (const auto& uniform : m_Uniforms) {
            if (uniform.Name == name) {
                glUniform4i(uniform.RendererID, value.x, value.y, value.z, value.w);
            }
        }
    }

    const ShaderUniforms& OpenGLShader::GetUniforms() const
    {
        return m_Uniforms;
    }
}
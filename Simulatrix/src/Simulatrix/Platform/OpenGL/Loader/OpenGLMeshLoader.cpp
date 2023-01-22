#include "simixpch.h"
#include "OpenGLMeshLoader.h"
#include <glad/glad.h>
#include "Simulatrix/Platform/OpenGL/OpenGLVertexArray.h"
#include "Simulatrix/Platform/OpenGL/OpenGLBuffer.h"

namespace Simulatrix {
    SceneMesh OpenGLMeshLoader::Load(ResourceMesh& t) {

        auto VAO = CreateRef<OpenGLVertexArray>();
        VAO->Bind();

        auto VBO = CreateRef<OpenGLVertexBuffer>(t.vertices);
        VBO->Bind();

        auto EBO = CreateRef<OpenGLIndexBuffer>(t.indices);
        EBO->Bind();

        BufferLayout layout{
            { ShaderDataType::Vec3, "a_Position" },
            { ShaderDataType::Vec3, "a_Normal" },
            { ShaderDataType::Vec2, "a_TexCoords" },
            { ShaderDataType::Vec3, "a_Tangent" },
            { ShaderDataType::Vec3, "a_Bitangent" },
            /*{ ShaderDataType::IVec3, "a_BoneIDs" },
            { ShaderDataType::Vec4, "a_Weights" },*/
        };
        VBO->SetLayout(layout);
        VAO->AddVertexBuffer(VBO);
        VAO->SetIndexBuffer(EBO);

        return SceneMesh(VAO, t.indices.size() * sizeof(uint32_t));
    }
}
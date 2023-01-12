#include "simixpch.h"
#include "OpenGLMeshLoader.h"
#include <glad/glad.h>
#include "Simulatrix/Platform/OpenGL/OpenGLVertexArray.h"
#include "Simulatrix/Platform/OpenGL/OpenGLBuffer.h"

namespace Simulatrix {
    SceneMesh OpenGLMeshLoader::Load(ResourceMesh& t) {
        auto VAO = new OpenGLVertexArray();
        VAO->Bind();
        
        auto VBO = new OpenGLVertexBuffer(t.vertices);
        VBO->Bind();

        auto EBO = new OpenGLIndexBuffer(t.indices);
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
        std::shared_ptr<VertexBuffer> VBO_P;
        VBO_P.reset(VBO);
        VAO->AddVertexBuffer(VBO_P);

        std::shared_ptr<IndexBuffer> EBO_P;
        EBO_P.reset(EBO);
        VAO->SetIndexBuffer(EBO_P);

        return SceneMesh(VAO, t.indices.size() * sizeof(unsigned int));
    }
}
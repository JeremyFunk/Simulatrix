#pragma once
#include "RenderCommand.h"
#include "Simulatrix/Scene/Scene.h"
#include "Simulatrix/Renderer/Shader.h"
#include <vector>
namespace Simulatrix {
    struct Mesh {
        std::shared_ptr<VertexArray> vertexArray;

        Mesh(std::shared_ptr<VertexArray> vertexArray) : vertexArray(vertexArray) {

        }
    };

    class Renderer {
    public:
        static void BeginScene(std::shared_ptr<Scene> scene);
        static void EndScene(std::shared_ptr<Scene> scene);

        static void Render(std::shared_ptr<Scene> scene);
        static void AddMesh(std::shared_ptr<Mesh> mesh) {
            s_Meshes.push_back(mesh);
        }
        static void AddMesh(Mesh mesh) {
            s_Meshes.push_back(std::make_shared<Mesh>(mesh));
        }
        static void AddShader(std::shared_ptr <Shader> shader) {
            s_Shaders.push_back(shader);
        }

        static inline RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
    private:
        static std::vector<std::shared_ptr<Mesh>> s_Meshes;
        static std::vector<std::shared_ptr<Shader>> s_Shaders;
    };
}
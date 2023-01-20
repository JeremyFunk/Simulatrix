#pragma once
#include "RenderCommand.h"
#include "Simulatrix/Scene/Scene.h"
#include "Simulatrix/Renderer/Shader.h"
#include <vector>
namespace Simulatrix {
    struct Mesh {
        Ref<VertexArray> vertexArray;

        Mesh(Ref<VertexArray> vertexArray) : vertexArray(vertexArray) {

        }
    };

    class Renderer {
    public:
        static void BeginScene(Ref<Scene> scene);
        static void EndScene(Ref<Scene> scene);

        static void Render(Ref<Scene> scene);
        static void AddMesh(Ref<Mesh> mesh) {
            s_Meshes.push_back(mesh);
        }
        static void AddMesh(Mesh mesh) {
            s_Meshes.push_back(std::make_shared<Mesh>(mesh));
        }

        static inline RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
    private:
        static std::vector<Ref<Mesh>> s_Meshes;
    };
}
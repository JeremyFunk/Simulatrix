#include "simixpch.h"
#include "Renderer.h"

namespace Simulatrix {
    std::vector<std::shared_ptr<Mesh>> Renderer::s_Meshes = std::vector<std::shared_ptr<Mesh>>();
    std::vector<std::shared_ptr<Shader>> Renderer::s_Shaders = std::vector<std::shared_ptr<Shader>>();

    void Renderer::BeginScene(std::shared_ptr<Scene> scene)
    {
    }
    void Renderer::EndScene(std::shared_ptr<Scene> scene)
    {
    }

    void Renderer::Render(std::shared_ptr<Scene> scene) {
        auto models = scene->GetAllEntitiesWith<ComponentMesh, ComponentTransform, ComponentShader>();
        for (auto& m : models) {
            auto [meshC, transformC, shaderC] = scene->GetComponents<ComponentMesh, ComponentTransform, ComponentShader>(m);

            auto& shader = s_Shaders[shaderC.RendererID];
            shader->Bind();

            auto& mesh = s_Meshes[meshC.RendererID];
            mesh->vertexArray->Bind();
            shader->SetUniform("u_modelMatrix", transformC.Transform);
            RenderCommand::DrawIndexed(mesh->vertexArray);
        }
    }
}
#include "simixpch.h"
#include "Renderer.h"
#include "Simulatrix/ResourceManager/ResourceManager.h"

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
        auto meshes = scene->GetAllEntitiesWith<ComponentMesh, ComponentTransform, ComponentShader>();
        for (auto& m : meshes) {
            auto [meshC, transformC, shaderC] = scene->GetComponents<ComponentMesh, ComponentTransform, ComponentShader>(m);

            auto& shader = s_Shaders[shaderC.RendererID];
            shader->Bind();

            auto& mesh = s_Meshes[meshC.RendererID];
            mesh->vertexArray->Bind();
            shader->SetUniform("u_modelMatrix", transformC.Transform);
            RenderCommand::DrawIndexed(mesh->vertexArray);
        }


        auto models = scene->GetAllEntitiesWith<ComponentModel, ComponentTransform, ComponentShader>();
        for (auto& m : models) {
            auto [modelC, transformC, shaderC] = scene->GetComponents<ComponentModel, ComponentTransform, ComponentShader>(m);

            auto& shader = s_Shaders[shaderC.RendererID];
            shader->Bind();
            
            auto& model = ResourceManager::Get()->GetModel(modelC.ModelID);

            for (auto& mesh : model.Meshes) {
                mesh.VAO->Bind();
                shader->SetUniform("u_modelMatrix", transformC.Transform);
                shader->SetUniform("u_textureDiffuse", model.Textures[0]->GetRendererID());
                model.Textures[0]->Bind(0);
                RenderCommand::DrawIndexed(mesh.VAO);
            }
        }
    }
}
#include "simixpch.h"
#include "Renderer.h"
#include "Simulatrix/ResourceManager/ResourceManager.h"

namespace Simulatrix {
    std::vector<Ref<Mesh>> Renderer::s_Meshes = std::vector<Ref<Mesh>>();
    std::vector<Ref<Shader>> Renderer::s_Shaders = std::vector<Ref<Shader>>();

    void Renderer::BeginScene(Ref<Scene> scene)
    {
    }
    void Renderer::EndScene(Ref<Scene> scene)
    {
    }

    void Renderer::Render(Ref<Scene> scene) {

        auto meshes = scene->GetAllEntitiesWith<ComponentMesh, ComponentTransform, ComponentShader>();
        auto v = scene->GetCamera()->GetViewMatrix();
        for (auto& m : meshes) {
            auto [meshC, transformC, shaderC] = scene->GetComponents<ComponentMesh, ComponentTransform, ComponentShader>(m);

            auto& shader = s_Shaders[shaderC.RendererID];
            shader->Bind();
            shader->SetUniform("u_viewMatrix", v);

            auto& mesh = s_Meshes[meshC.RendererID];
            mesh->vertexArray->Bind();
            shader->SetUniform("u_modelMatrix", transformC.GetTransform());
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
                shader->SetUniform("u_modelMatrix", transformC.GetTransform());
                shader->SetUniform("u_viewMatrix", v);
                shader->SetUniform("u_textureDiffuse", model.Textures[0]->GetRendererID());
                model.Textures[0]->Bind(0);
                RenderCommand::DrawIndexed(mesh.VAO);
            }
        }
    }
}
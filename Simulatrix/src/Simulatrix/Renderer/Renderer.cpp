#include "simixpch.h"
#include "Renderer.h"
#include "Simulatrix/ResourceManager/ResourceManager.h"

namespace Simulatrix {
    std::vector<Ref<Mesh>> Renderer::s_Meshes = std::vector<Ref<Mesh>>();
    std::unordered_map<UUID, Ref<Shader>> Renderer::s_Shaders = std::unordered_map<UUID, Ref<Shader>>();

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

            auto& shader = s_Shaders[shaderC.ID];
            shader->Bind();
            shader->SetUniform("u_viewMatrix", v);

            auto& mesh = s_Meshes[meshC.ID];
            mesh->vertexArray->Bind();
            shader->SetUniform("u_modelMatrix", transformC.GetTransform());
            RenderCommand::DrawIndexed(mesh->vertexArray);
        }

        auto models = scene->GetAllEntitiesWith<ComponentModel, ComponentTransform, ComponentShader, ComponentTextureMaterial>();
        for (auto& m : models) {
            auto [modelC, transformC, shaderC, textureC] = scene->GetComponents<ComponentModel, ComponentTransform, ComponentShader, ComponentTextureMaterial>(m);

            auto& shader = s_Shaders[shaderC.ID];
            shader->Bind();
            
            auto& model = ResourceManager::Get()->GetModel(modelC.ID);

            for (auto& mesh : model.Meshes) {
                mesh.VAO->Bind();
                shader->SetUniform("u_modelMatrix", transformC.GetTransform());
                shader->SetUniform("u_viewMatrix", v);
                //shader->SetUniform("u_textureDiffuse", model.Textures[0]->GetRendererID());
                auto textureId = ResourceManager::Get()->GetTexture(textureC.ID)->GetRendererID();
                shader->SetUniform("u_textureDiffuse", textureId);
                ResourceManager::Get()->GetTexture(textureC.ID)->Bind();
                RenderCommand::DrawIndexed(mesh.VAO);
            }
        }
    }
}
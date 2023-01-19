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
        auto v = scene->GetCamera()->GetViewMatrix();
        auto models = scene->GetAllEntitiesWith<ComponentModel, ComponentTransform, ComponentShader>();
        for (auto& m : models) {
            auto [modelC, transformC, shaderC] = scene->GetComponents<ComponentModel, ComponentTransform, ComponentShader>(m);

            auto& shader = s_Shaders[shaderC.ID];
            shader->Bind();
            
            auto& model = ResourceManager::Get()->GetModel(modelC.ID);
            shader->SetUniform("u_modelMatrix", transformC.GetTransform());
            shader->SetUniform("u_viewMatrix", v);

            if (scene->HasComponents<ComponentTextureMaterial>(m)) {
                auto& textureC = scene->GetComponent< ComponentTextureMaterial>(m);
                if (textureC.Diffuse != nullptr) {
                    shader->SetUniform("u_textureDiffuse", textureC.Diffuse->GetRendererID());
                    textureC.Diffuse->Bind();
                }
            }
            for (auto& mesh : model.Meshes) {
                mesh.VAO->Bind();
                RenderCommand::DrawIndexed(mesh.VAO);
            }
        }
    }
}
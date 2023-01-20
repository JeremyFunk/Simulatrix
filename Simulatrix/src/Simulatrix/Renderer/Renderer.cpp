#include "simixpch.h"
#include "Renderer.h"
#include "Simulatrix/ResourceManager/ResourceManager.h"

namespace Simulatrix {
    std::vector<Ref<Mesh>> Renderer::s_Meshes = std::vector<Ref<Mesh>>();

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
            if (shaderC.ShaderRef == nullptr) {
                continue;
            }
            shaderC.ShaderRef->Bind();
            
            auto& model = ResourceManager::Get()->GetModel(modelC.ID);
            shaderC.ShaderRef->SetUniform("u_modelMatrix", transformC.GetTransform());
            shaderC.ShaderRef->SetUniform("u_viewMatrix", v);

            if (scene->HasComponents<ComponentTextureMaterial>(m)) {
                auto& textureC = scene->GetComponent< ComponentTextureMaterial>(m);
                if (textureC.Diffuse != nullptr) {
                    shaderC.ShaderRef->SetUniform("u_textureDiffuse", textureC.Diffuse->GetRendererID());
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
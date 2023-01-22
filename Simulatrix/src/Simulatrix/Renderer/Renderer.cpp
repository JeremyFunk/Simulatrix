#include "simixpch.h"
#include "Renderer.h"
#include "Simulatrix/ResourceManager/ResourceManager.h"

namespace Simulatrix {
    std::vector<Ref<Mesh>> Renderer::s_Meshes = std::vector<Ref<Mesh>>();
    glm::mat4 Renderer::s_Projection = glm::mat4(1.0);

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
            
            shaderC.ShaderRef->SetUniform("u_modelMatrix", transformC.GetTransform());
            shaderC.ShaderRef->SetUniform("u_viewMatrix", v);
            shaderC.ShaderRef->SetUniform("u_projectionMatrix", s_Projection);

            if (scene->HasComponents<ComponentTextureMaterial>(m)) {
                auto& textureC = scene->GetComponent< ComponentTextureMaterial>(m);
                if (textureC.Diffuse != nullptr) {
                    shaderC.ShaderRef->SetUniform("u_textureDiffuse", textureC.Diffuse->GetRendererID());
                    textureC.Diffuse->Bind();
                }
            }
            for (auto& mesh : modelC.Model->Meshes) {
                mesh.VAO->Bind();
                RenderCommand::DrawIndexed(mesh.VAO);
            }
        }
    }
}
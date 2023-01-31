#include "simixpch.h"
#include "SceneRenderer.h"
#include "Simulatrix/Renderer/RenderCommand.h"

namespace Simulatrix {
    SceneRenderer::SceneRenderer(Ref<Scene> scene) : m_Scene(scene) {

    }

    void SceneRenderer::Init()
    {
        
    }

    void SceneRenderer::SetScene(Ref<Scene> scene)
    {
        m_Scene = scene;
    }

    void SceneRenderer::BeginScene()
    {
        auto& cam = m_Scene->GetCamera();
        m_ViewMatrix = cam->GetViewMatrix();
        m_ProjectionMatrix = glm::perspective(glm::radians(cam->GetFOV()), (float)m_Width / (float)m_Height, cam->GetNearPlane(), cam->GetFarPlane());
    }

    void SceneRenderer::EndScene()
    {

    }

    void SceneRenderer::WaitForRender() {
        auto models = m_Scene->GetAllEntitiesWith<ComponentRenderable>();

        for (auto& m : models) {
            auto [render, transformC] = m_Scene->GetComponents<ComponentRenderable, ComponentTransform>(m);
            render.RenderPipeline->Bind();
            // TODO put in render pipeline with uniform buffers
            render.RenderPipeline->GetShader()->SetUniform("u_modelMatrix", transformC.GetTransform());
            render.RenderPipeline->GetShader()->SetUniform("u_viewMatrix", m_ViewMatrix);
            render.RenderPipeline->GetShader()->SetUniform("u_projectionMatrix", m_ProjectionMatrix);
            render.RenderPipeline->GetShader()->SetUniform("u_entityId", (uint32_t)m);


            // TODO automate with material component binds
            if (m_Scene->HasComponents<ComponentMaterial>(m)) {
                auto& materialC = m_Scene->GetComponent<ComponentMaterial>(m);
                if(materialC.Material != nullptr)
                    materialC.Material->Bind(render.RenderPipeline->GetShader());
            }

            
            for (auto& mesh : render.Model->Meshes) {
                mesh.VAO->Bind();
                RenderCommand::DrawIndexed(mesh.VAO);
            }
        }
    }

    void SceneRenderer::SetViewportSize(uint32_t width, uint32_t height)
    {
        m_Width = width;
        m_Height = height;
    }
}
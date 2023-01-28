#pragma once
#include <Simulatrix/Scene/Scene.h>

namespace Simulatrix {
    struct SceneRendererOptions {

    };

    class SceneRenderer {
    public:
        SceneRenderer(Ref<Scene> scene);

        void Init();

        void SetScene(Ref<Scene> scene);

        void BeginScene();
        void EndScene();
        void WaitForRender();

        void SetViewportSize(uint32_t width, uint32_t height);
        glm::mat4 GetViewMatrix() const { return m_ViewMatrix; }
        glm::mat4 GetProjectionMatrix() const { return m_ProjectionMatrix; }
    private:
        int m_Width, m_Height;
        Ref<Scene> m_Scene;
        glm::mat4 m_ViewMatrix, m_ProjectionMatrix;
    };
}
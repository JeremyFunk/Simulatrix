#pragma once
#include "Core.h"
#include "Simulatrix/Core/Window.h"
#include <Simulatrix/Events/Event.h>
#include <Simulatrix/Core/Layer.h>
#include <Simulatrix/Core/LayerStack.h>
#include <Simulatrix/Events/ApplicationEvent.h>
#include <Simulatrix/ImGui/ImGuiLayer.h>
#include <Simulatrix/Renderer/Shader.h>
#include <Simulatrix/Renderer/Buffer.h>
#include <Simulatrix/Renderer/VertexArray.h>
#include <Simulatrix/Renderer/SceneRenderer.h>
#include <Simulatrix/Core/Camera.h>
#include <Simulatrix/Scene/Scene.h>
#include <Simulatrix/Renderer/Framebuffer.h>

#include <Simulatrix/ResourceManager/ResourceManager.h>
namespace Simulatrix {
    class Application
    {
    public:
        Application();
        virtual ~Application();
        void Run();

        void OnEvent(Event& e);
        Window& GetWindow() { return *m_Window; }
        static Application& Get() { return *s_Instance; }

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);
        Ref<Scene>& GetActiveScene() {
            return m_ActiveScene;
        }
        Ref<SceneRenderer>& GetSceneRenderer() {
            return m_SceneRenderer;
        }
        void SetViewportSize(uint32_t width, uint32_t height);
    private:
        bool OnWindowClosed(WindowCloseEvent& e); 

        Scope<Window> m_Window;
        bool m_Running = true;
        LayerStack m_LayerStack;
    private:
        static Application* s_Instance;
        float m_LastFrameTime = 0.0f;
        ImGuiLayer* m_ImGuiLayer;
        Ref<Scene> m_ActiveScene;
        Ref<SceneRenderer> m_SceneRenderer;
    };
    // To be defined in client.
    Application* CreateApplication();
}


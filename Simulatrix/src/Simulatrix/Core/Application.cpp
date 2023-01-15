#include "simixpch.h"
#include "Simulatrix/Debug/Log.h"
#include "Application.h"
#include "Simulatrix/Renderer/Renderer.h"
#include "Simulatrix/Renderer/RendererAPI.h"
#include <GLFW/glfw3.h>
#include "Simulatrix/Core/OrthographicCamera.h"
#include "IOWrapper.h"
#include "Simulatrix/Core/Input.h"
namespace Simulatrix {

    Application* Application::s_Instance = nullptr;

    Application::Application() {
        m_ResourceManager.reset(new ResourceManager());
        auto temp = m_ResourceManager->GetIO()->GetCurrentDir();
        SIMIX_CORE_INFO("Starting in directory {0}", m_ResourceManager->GetIO()->GetCurrentDir().PathString);

        m_Window = Scope<Window>(Window::Create());
        m_Window->SetEventCallback(SIMIX_BIND_EVENT_FN(Application::OnEvent));
        SIMIX_CORE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;

        RenderCommand::Init();
        m_ImGuiLayer = new ImGuiLayer();
        m_ImGuiLayer->OnAttach();

        m_ActiveScene.reset(new Scene());
    }
    Application::~Application() {

    }

    void Application::OnEvent(Event& e) {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(SIMIX_BIND_EVENT_FN(Application::OnWindowClosed));

        //SIMIX_CORE_TRACE("{0}", e.ToString());

        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
            (*--it)->OnEvent(e);
            if (e.Handled)
                break;
        }
    }

    void Application::Run() {
        while (m_Running) {
            Input::PollInputs();
            m_ResourceManager->Update();
            Renderer::BeginScene(m_ActiveScene);

            float time = (float)glfwGetTime();
            Timestep timestep = time - m_LastFrameTime;
            m_LastFrameTime = time;

            for (Layer* layer : m_LayerStack)
                layer->OnUpdate(timestep);

            for (Layer* layer : m_LayerStack)
                layer->OnPreRender();
            for (Layer* layer : m_LayerStack)
                layer->OnRender();
            Renderer::Render(m_ActiveScene);
            for (Layer* layer : m_LayerStack)
                layer->OnPostRender();

            m_ImGuiLayer->Begin();

            for (Layer* layer : m_LayerStack)
                layer->OnPreRenderOverlay();
            for (Layer* layer : m_LayerStack)
                layer->OnRenderOverlay();
            for (Layer* layer : m_LayerStack)
                layer->OnPostRenderOverlay();

            m_ImGuiLayer->End();

            Renderer::EndScene(m_ActiveScene);
            m_Window->OnUpdate();
        }
    }

    bool Application::OnWindowClosed(WindowCloseEvent& e) {
        m_Running = false;
        return true;
    }

    void Application::PushLayer(Layer* layer) {
        m_LayerStack.PushLayer(layer);
    }

    void Application::PushOverlay(Layer* overlay) {
        m_LayerStack.PushOverlay(overlay);
    }
}
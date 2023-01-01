#pragma once
#include "Core.h"
#include "Simulatrix/Core/Window.h"
#include <Simulatrix/Events/Event.h>
#include <Simulatrix/Core/Layer.h>
#include <Simulatrix/Core/LayerStack.h>
#include <Simulatrix/Events/ApplicationEvent.h>
#include <Simulatrix/ImGui/ImGuiLayer.h>

int main(int argc, char** argv);

namespace Simulatrix {
    class SIMIX_API Application
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
    private:
        bool OnWindowClosed(WindowCloseEvent& e);

        Scope<Window> m_Window;
        bool m_Running = true;
        LayerStack m_LayerStack;
    private:
        static Application* s_Instance;
        float m_LastFrameTime = 0.0f;
        ImGuiLayer* m_ImGuiLayer;
        friend int ::main(int argc, char** argv);
    };
    // To be defined in client.
    Application* CreateApplication();
}


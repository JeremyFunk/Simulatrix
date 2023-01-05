#include "simixpch.h"
#include "Simulatrix/Debug/Log.h"
#include "Application.h"
#include "Simulatrix/Renderer/Renderer.h"
#include <GLFW/glfw3.h>
#include "Simulatrix/Core/OrthographicCamera.h"
namespace Simulatrix {

    Application* Application::s_Instance = nullptr;
#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)


    Application::Application() {
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
        SIMIX_CORE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);

        m_VertexArray.reset(VertexArray::Create());

        float vertices[3 * 3 + 3 * 4] = {
            -0.5, -0.5, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            0.5, -0.5, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
            0.0, 0.5, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        };
        auto vertexBuffer = std::make_shared<VertexBuffer>(VertexBuffer::Create(vertices, sizeof(vertices)));
        BufferLayout layout{
            { ShaderDataType::Vec3, "a_Position" },
            { ShaderDataType::Vec4, "a_Color" },
        };
        vertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vertexBuffer);


        unsigned int indices[3] = { 0, 1, 2 };
        m_VertexArray->SetIndexBuffer(std::make_shared<IndexBuffer>(IndexBuffer::Create(indices, 3)));

        std::string vertexSrc = R"(
            #version 330 core
            
            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;
            out vec4 p_Color;

            void main(){
                gl_Position = vec4(a_Position, 1.0);
                p_Color = a_Color;
            }
        )";
        std::string fragmentSrc = R"(
            #version 330 core
            out vec4 color;
            in vec4 p_Color;
            void main(){
                color = p_Color;
            }
        )";

        m_Shader.reset(new Shader(vertexSrc, fragmentSrc));


        m_Camera.reset(new OrthographicCamera());
    }
    Application::~Application() {

    }

    void Application::OnEvent(Event& e) {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClosed));

        //SIMIX_CORE_TRACE("{0}", e.ToString());

        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
            (*--it)->OnEvent(e);
            if (e.Handled)
                break;
        }
    }

    void Application::Run() {
        while (m_Running) {
            float time = (float)glfwGetTime();
            Timestep timestep = time - m_LastFrameTime;
            m_LastFrameTime = time;

            m_Camera->Update(timestep);

            RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.f });
            RenderCommand::Clear();
            m_Shader->Bind();
            Renderer::BeginScene();
            Renderer::Submit(m_VertexArray);
            Renderer::EndScene();


            for (Layer* layer : m_LayerStack)
                layer->OnUpdate(timestep);

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
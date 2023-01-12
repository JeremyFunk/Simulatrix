
#include <Simulatrix.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace Simulatrix;

class ExampleLayer : public Layer {

public:
    ExampleLayer()
        : Layer("Example") {

    }

    void OnAttach() {
        std::shared_ptr<VertexArray> vertexArray;
        vertexArray.reset(VertexArray::Create());

        float vertices[3 * 3 + 3 * 4] = {
            -0.5, -0.5, -2.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            0.5, -0.5, -2.0f, 0.0f, 1.0f, 0.0f, 1.0f,
            0.0, 0.5, -2.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        };
        std::shared_ptr<VertexBuffer> vertexBuffer;
        vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
        BufferLayout layout{
            { ShaderDataType::Vec3, "a_Position" },
            { ShaderDataType::Vec4, "a_Color" },
        };
        vertexBuffer->SetLayout(layout);
        vertexArray->AddVertexBuffer(vertexBuffer);


        unsigned int indices[3] = { 0, 1, 2 };
        std::shared_ptr<IndexBuffer> indexBuffer;
        indexBuffer.reset(IndexBuffer::Create(indices, 3));
        vertexArray->SetIndexBuffer(indexBuffer);

        Renderer::AddMesh(Mesh(vertexArray));

        std::string vertexSrc = R"(
            #version 330 core
            
            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;
            out vec4 p_Color;
            uniform mat4 u_projectionMatrix;
            uniform mat4 u_viewMatrix;
            uniform mat4 u_modelMatrix;

            void main(){
                gl_Position = u_projectionMatrix * u_viewMatrix * u_modelMatrix * vec4(a_Position, 1.0);
                p_Color = a_Color;
            }
        )";
        std::string fragmentSrc = R"(
            #version 330 core
            out vec4 color;
            in vec4 p_Color;
            uniform float u_colorAdd;
            void main(){
                color = p_Color + vec4(u_colorAdd * 0.1);
            }
        )";
        m_Shader.reset(Shader::Create(vertexSrc, fragmentSrc));
        ShaderUniforms uniforms = {
            { ShaderDataType::Float, "u_colorAdd" },
            { ShaderDataType::Mat4, "u_viewMatrix" },
            { ShaderDataType::Mat4, "u_projectionMatrix" },
            { ShaderDataType::Mat4, "u_modelMatrix" }
        };
        m_Shader->AddUniforms(uniforms);
        std::string vertexSrc2 = R"(
            #version 330 core
            
            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec3 a_Normal;
            layout(location = 2) in vec2 a_TexCoords;
            out vec2 p_TextureCoords;
            uniform mat4 u_projectionMatrix;
            uniform mat4 u_viewMatrix;
            uniform mat4 u_modelMatrix;

            void main(){
                gl_Position = u_projectionMatrix * u_viewMatrix * vec4(a_Position, 1.0);
                p_TextureCoords = a_TexCoords;
            }
        )";
        std::string fragmentSrc2 = R"(
            #version 330 core
            out vec4 color;
            in vec2 p_TextureCoords;
            uniform sampler2D u_textureDiffuse;
            void main(){
                color = texture(u_textureDiffuse, p_TextureCoords);
            }
        )";
        m_Shader2.reset(Shader::Create(vertexSrc2, fragmentSrc2));
        ShaderUniforms uniforms2 = {
            { ShaderDataType::Int, "u_textureDiffuse" },
            { ShaderDataType::Mat4, "u_viewMatrix" },
            { ShaderDataType::Mat4, "u_projectionMatrix" },
            { ShaderDataType::Mat4, "u_modelMatrix" }
        };
        m_Shader2->AddUniforms(uniforms2);
        
        Renderer::AddShader(m_Shader);
        Renderer::AddShader(m_Shader2);
        m_Camera.reset(new ProjectionCamera());

        //auto e = Application::Get().GetActiveScene()->CreateEntity();
        //e.AddComponent<ComponentMesh>(0);
        //e.AddComponent<ComponentShader>(0);
        //e.AddComponent<ComponentTransform>(glm::mat4(1.0));

        auto e2 = Application::Get().GetActiveScene()->CreateEntity();
        e2.AddComponent<ComponentModel>(0);
        e2.AddComponent<ComponentShader>(1);
        e2.AddComponent<ComponentTransform>(glm::mat4(1.0));
    }
    void OnDetach() {}
    void OnUpdate(Timestep ts) {
        /*if (Input::IsKeyPressed(Key::Left)) {
            m_Camera->SetPosition(m_Camera->GetPosition() + glm::vec3(-0.01, 0.0, 0.0));
        }
        if (Input::IsKeyPressed(Key::Right)) {
            m_Camera->SetPosition(m_Camera->GetPosition() + glm::vec3(0.01, 0.0, 0.0));
        }
        if (Input::IsKeyPressed(Key::Up)) {
            m_Camera->SetPosition(m_Camera->GetPosition() + glm::vec3(0.0, 0.01, 0.0));
        }
        if (Input::IsKeyPressed(Key::Down)) {
            m_Camera->SetPosition(m_Camera->GetPosition() + glm::vec3(0.0, -0.01, 0.0));
        }*/

        totalTime += ts;
        m_Camera->Update(ts);
        RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.f });
        RenderCommand::Clear();
        
        auto e = Application::Get().GetActiveScene()->GetAllEntitiesWith<ComponentTransform>();
        auto t = Application::Get().GetActiveScene()->GetComponent<ComponentTransform>(e[0]);

        t.Transform[3][0] = totalTime * .1;

        Application::Get().GetActiveScene()->ReplaceComponent<ComponentTransform>(e[0], t);

        auto& window = Application::Get().GetWindow();
        glm::mat4 projection = glm::perspective(glm::radians(45.f), (float)window.GetWidth() / (float)window.GetHeight(), 0.1f, 100.0f);


        m_Shader->Bind();
        m_Shader->SetUniform("u_colorAdd", totalTime);
        m_Shader->SetUniform("u_viewMatrix", m_Camera->GetViewMatrix());
        m_Shader->SetUniform("u_projectionMatrix", projection);


        m_Shader2->Bind();
        
        m_Shader2->SetUniform("u_viewMatrix", m_Camera->GetViewMatrix());
        m_Shader2->SetUniform("u_projectionMatrix", projection);
    }
    void OnEvent(Event& e) {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<KeyPressedEvent>(SIMIX_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));
    }

    bool OnKeyPressedEvent(KeyPressedEvent& e) {
        return false;
    }

private:
    float totalTime = 0.f;
    std::shared_ptr<Shader> m_Shader;
    std::shared_ptr<Shader> m_Shader2;
    std::shared_ptr<Camera> m_Camera;
};

class Sandbox : public Simulatrix::Application
{
public:
    Sandbox() {
        PushLayer(new ExampleLayer());
    }

    ~Sandbox() {

    }
};

Simulatrix::Application* Simulatrix::CreateApplication() {
    return new Sandbox();
}
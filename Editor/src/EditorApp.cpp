
#include <Simulatrix.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "ImGui/EditorLayer.h"
#include <imgui.h>
#include "ImGui/SceneHierarchy.h"
#include "ImGui/ContentBrowser.h"
#include "ImGui/Properties.h"
#include "ImGui/IconLibrary.h"
#include "Simulatrix/Core/UUID.h"

using namespace Simulatrix;

class ExampleLayer : public Layer {

public:
    ExampleLayer()
        : Layer("Example") {

    }

    void OnPreRender() {
        m_Framebuffer->Bind();
    }
    void OnPostRender() {
        m_Framebuffer->Unbind();
    }

    void OnAttach() {
        FramebufferSpecification fbSpec;
        fbSpec.Attachments = { FramebufferTextureFormat::RGBA8, FramebufferTextureFormat::RED_INTEGER, FramebufferTextureFormat::Depth };
        fbSpec.Width = 1280;
        fbSpec.Height = 720;
        m_Framebuffer = Framebuffer::Create(fbSpec);

        auto vertexArray = Ref<VertexArray>(VertexArray::Create());

        float vertices[3 * 3 + 3 * 4] = {
            -0.5, -0.5, -2.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            0.5, -0.5, -2.0f, 0.0f, 1.0f, 0.0f, 1.0f,
            0.0, 0.5, -2.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        };
        auto vertexBuffer = Ref<VertexBuffer>(VertexBuffer::Create(vertices, sizeof(vertices)));
        BufferLayout layout{
            { ShaderDataType::Vec3, "a_Position" },
            { ShaderDataType::Vec4, "a_Color" },
        };
        vertexBuffer->SetLayout(layout);
        vertexArray->AddVertexBuffer(vertexBuffer);


        unsigned int indices[3] = { 0, 1, 2 };
        auto indexBuffer = Ref<IndexBuffer>(IndexBuffer::Create(indices, 3));
        vertexArray->SetIndexBuffer(indexBuffer);

        Renderer::AddMesh(Mesh(vertexArray));

        std::string vertexSrc = R"(
            #version 330 core
            
            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec3 a_Normal;
            layout(location = 2) in vec2 a_TexCoords;
            uniform mat4 u_projectionMatrix;
            uniform mat4 u_viewMatrix;
            uniform mat4 u_modelMatrix;

            void main(){
                gl_Position = u_projectionMatrix * u_viewMatrix * u_modelMatrix * vec4(a_Position, 1.0);
            }
        )";
        std::string fragmentSrc = R"(
            #version 330 core
            out vec4 color;
            void main(){
                color = vec4(1.0);
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
                gl_Position = u_projectionMatrix * u_viewMatrix * u_modelMatrix * vec4(a_Position, 1.0);
                p_TextureCoords = a_TexCoords;
            }
        )";
        std::string fragmentSrc2 = R"(
            #version 330 core
            out vec4 color;
            in vec2 p_TextureCoords;
            uniform sampler2D u_textureDiffuse;
            void main(){
                //color = vec4(1.0);
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
        
        m_ShaderID1 = Renderer::AddShader(m_Shader);
        m_ShaderID2 = Renderer::AddShader(m_Shader2);
        m_Camera.reset(new ProjectionCamera());
        Application::Get().GetActiveScene()->SetCamera(m_Camera);
        Application::Get().GetActiveScene()->SetDefaultShader(m_ShaderID2);

        //auto e = Application::Get().GetActiveScene()->CreateEntity();
        //e.AddComponent<ComponentMesh>(0);
        //e.AddComponent<ComponentShader>(0);
        //e.AddComponent<ComponentTransform>(glm::mat4(1.0));


        auto e2 = Application::Get().GetActiveScene()->CreateEntity();
        e2.AddComponent<ComponentModel>(ResourceManager::Get()->GetModelID(Path("C:\\Users\\Jerem\\Documents\\GitHub\\Simulatrix\\Editor\\resources\\raw\\assets\\Backpack\\backpack.obj", PathType::File)));
        e2.AddComponent<ComponentShader>(m_ShaderID2);
        e2.AddComponent<ComponentTag>("Backpack");
        e2.AddComponent<ComponentTransform>();
        e2.AddComponent<ComponentTextureMaterial>(ResourceManager::Get()->GetTexture(Path("C:\\Users\\Jerem\\Documents\\GitHub\\Simulatrix\\Editor\\resources\\raw\\assets\\Backpack\\diffuse.jpg", PathType::File)));

        m_IconLib.reset(new IconLibrary());
        m_IconLib->LoadIconByName("add");
        m_IconLib->LoadIconByName("adjust");
        m_IconLib->LoadIconByName("bmp");
        m_IconLib->LoadIconByName("clear");
        m_IconLib->LoadIconByName("checkbox-unchecked");
        m_IconLib->LoadIconByName("checkbox-checked");
        m_IconLib->LoadIconByName("close");
        m_IconLib->LoadIconByName("copy");
        m_IconLib->LoadIconByName("create");
        m_IconLib->LoadIconByName("details");
        m_IconLib->LoadIconByName("document");
        m_IconLib->LoadIconByName("done");
        m_IconLib->LoadIconByName("done-double");
        m_IconLib->LoadIconByName("error");
        m_IconLib->LoadIconByName("file-add");
        m_IconLib->LoadIconByName("file-audio");
        m_IconLib->LoadIconByName("file-delete");
        m_IconLib->LoadIconByName("file-edit");
        m_IconLib->LoadIconByName("file-filter");
        m_IconLib->LoadIconByName("file-image");
        m_IconLib->LoadIconByName("file-video");
        m_IconLib->LoadIconByName("folder");
        m_IconLib->LoadIconByName("folder-add");
        m_IconLib->LoadIconByName("folder-delete");
        m_IconLib->LoadIconByName("folder-edit");
        m_IconLib->LoadIconByName("folder-open");
        m_IconLib->LoadIconByName("folder-search");
        m_IconLib->LoadIconByName("help");
        m_IconLib->LoadIconByName("info");
        m_IconLib->LoadIconByName("jpg");
        m_IconLib->LoadIconByName("menu");
        m_IconLib->LoadIconByName("menu-circle");
        m_IconLib->LoadIconByName("mp3");
        m_IconLib->LoadIconByName("png");
        m_IconLib->LoadIconByName("remove");
        m_IconLib->LoadIconByName("save");
        m_IconLib->LoadIconByName("save-all");
        m_IconLib->LoadIconByName("save-as");


        m_SceneHierarchy.reset(new SceneHierarchy(Application::Get().GetActiveScene(), m_IconLib));
        m_ContentBrowser.reset(new ContentBrowser(m_IconLib));
        m_Properties.reset(new Properties());
        m_ToggleUtil.reset(new ToggleUtil());
        //std::function<bool(bool)> fn = std::bind(Test, this, &std::placeholders::_1);
        std::function<bool(bool)> fn = [this](bool pressed) {
            SIMIX_CORE_INFO("PRESSEDEDED {0}", pressed);
            m_Camera->SetFreecam(pressed);
            return false;
        };
        m_ToggleUtil->RegisterToggle(Key::F, fn);

    }

    void OnDetach() {}


    void OnUpdate(Timestep ts) {
        totalTime += ts;
        m_Camera->Update(ts);
        
        auto e = Application::Get().GetActiveScene()->GetAllEntitiesWith<ComponentTransform>();
        auto t = Application::Get().GetActiveScene()->GetComponent<ComponentTransform>(e[0]);

        Application::Get().GetActiveScene()->ReplaceComponent<ComponentTransform>(e[0], t);

    }

    void OnRender() {
        RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.f });
        RenderCommand::Clear();

        auto& window = Application::Get().GetWindow();

        glm::mat4 projection = glm::perspective(glm::radians(45.f), (float)m_ViewportSize.x / (float)m_ViewportSize.y, 0.1f, 100.0f);

        m_Shader->Bind();
        m_Shader->SetUniform("u_colorAdd", totalTime);
        m_Shader->SetUniform("u_projectionMatrix", projection);

        m_Shader2->Bind();

        m_Shader2->SetUniform("u_projectionMatrix", projection);
    }

    void OnRenderOverlay()
    {
        ImGui::DockSpaceOverViewport();

        ImGui::Begin("Viewport");
        glm::vec2 viewportSize = *((glm::vec2*)&ImGui::GetContentRegionAvail());
        if (m_ViewportSize != viewportSize) {
            m_Framebuffer->Resize(m_ViewportSize.x, m_ViewportSize.y);
        }
        m_ViewportSize = viewportSize;
        ImGui::Image((void*)m_Framebuffer->GetColorAttachmentRendererID(), ImVec2(viewportSize.x, viewportSize.y), ImVec2(0, 1), ImVec2(1, 0));

        if (ImGui::BeginDragDropTarget()) {
            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM")) {
                const char* path = (const char*)payload->Data;
                
                Application::Get().GetActiveScene()->FileDropped(Path(path, PathType::File));

                ImGui::EndDragDropTarget();
            }
        }
        ImGui::End();

        m_SceneHierarchy->Render();
        m_ContentBrowser->Render();
        m_Properties->Render();
    }


    void OnEvent(Event& e) {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<KeyPressedEvent>(SIMIX_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));
    }

    bool OnKeyPressedEvent(KeyPressedEvent& e) {
        return m_ToggleUtil->OnKeyPressed(e);
    }

private:
    float totalTime = 0.f;
    Ref<Shader> m_Shader;
    Ref<Shader> m_Shader2;
    Simulatrix::UUID m_ShaderID1;
    Simulatrix::UUID m_ShaderID2;
    Ref<ProjectionCamera> m_Camera;
    Ref<Framebuffer> m_Framebuffer;
    Ref<SceneHierarchy> m_SceneHierarchy;
    Ref<ContentBrowser> m_ContentBrowser;
    Ref<Properties> m_Properties;
    Ref<ToggleUtil> m_ToggleUtil;
    Ref<IconLibrary> m_IconLib;
    glm::vec2 m_ViewportSize;
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
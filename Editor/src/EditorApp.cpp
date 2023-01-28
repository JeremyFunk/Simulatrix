
#include <Simulatrix.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ImGui/EditorLayer.h"
#include <ImGui/imgui.h>
#include "ImGui/SceneHierarchy.h"
#include "ImGui/ContentBrowser.h"
#include "ImGui/Toolbar.h"
#include "ImGui/IconLibrary.h"
#include "ImGui/ShaderEditor.h"
#include "ImGui/MainMenu.h"
#include "Simulatrix/Core/UUID.h"
#include "DiffuseShader.h"
#include <ImGuizmo.h>
#include "Simulatrix/Scene/SceneSerializer.h"
#include "Simulatrix/Util/MathUtil.h"
#include "CommandStack/CommandStack.h"
#include "CommandStack/CommandTransform.h"
#include "Actions/ActionTransform.h"

using namespace Simulatrix;

class ExampleLayer : public Layer {

public:
    ExampleLayer(Ref<Scene> scene)
        : Layer("Example"), m_Scene(scene) {

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

        //auto diffuseShader = DiffuseShader(Path("C:\\Users\\Jerem\\Documents\\GitHub\\Simulatrix\\Editor\\resources\\raw\\shaders\\diffuse\\vs.vs", PathType::File), Path("C:\\Users\\Jerem\\Documents\\GitHub\\Simulatrix\\Editor\\resources\\raw\\shaders\\diffuse\\fs.fs", PathType::File));
        m_Camera.reset(new ProjectionCamera());
        m_Scene->SetCamera(m_Camera);

        //auto e = m_Scene->CreateEntity();
        //e.AddComponent<ComponentMesh>(0);
        //e.AddComponent<ComponentShader>(0);
        //e.AddComponent<ComponentTransform>(glm::mat4(1.0));

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
        m_IconLib->LoadIconByName("move");
        m_IconLib->LoadIconByName("rotate");
        m_IconLib->LoadIconByName("scale");
        m_IconLib->LoadIconByName("model-edit");
        m_IconLib->LoadIconByName("grid");

        m_SceneHierarchy.reset(new SceneHierarchy(m_Scene, m_IconLib));
        m_ContentBrowser.reset(new ContentBrowser(m_IconLib));
        m_Toolbar.reset(new Toolbar(m_Scene, m_IconLib));
        m_MainMenu.reset(new MainMenu(m_Scene, m_IconLib));
        m_ShaderEditor.reset(new ShaderEditor(m_Scene, m_IconLib));
        m_ToggleUtil.reset(new ToggleUtil());
        //std::function<bool(bool)> fn = std::bind(Test, this, &std::placeholders::_1);
        m_ToggleUtil->RegisterToggle(Key::F, [this](bool pressed) {
            m_Camera->SetFreecam(pressed);
        return false;
            });

        m_ToggleUtil->RegisterStatelessToggle(Key::S, [this]() {
            m_Toolbar->SetTranslationMode(ImGuizmo::SCALE);
        return false;
            });
        m_ToggleUtil->RegisterStatelessToggle(Key::R, [this]() {
            m_Toolbar->SetTranslationMode(ImGuizmo::ROTATE);
        return false;
            });
        m_ToggleUtil->RegisterStatelessToggle(Key::G, [this]() {
            m_Toolbar->SetTranslationMode(ImGuizmo::TRANSLATE);
        return false;
            });

        m_Action = nullptr;

        // GRID
        auto gridShader = ResourceManager::GetOrLoadShader(Path(ResourceManager::GetIO()->GetCurrentDir().PathString + "\\resources\\raw\\shaders\\grid\\grid.glsl", PathType::File));
        PipelineSpecification gridPipelineSpec;
        gridPipelineSpec.Shader = gridShader;
        gridPipelineSpec.BackfaceCulling = false;
        gridPipelineSpec.DebugName = "Grid Pipeline";
        auto gridPipeline = Pipeline::Create(gridPipelineSpec);
        m_Scene->AddPipeline(gridPipeline);
        
        auto e = m_Scene->CreateEntity();
        e.AddComponent<ComponentID>();
        e.AddComponent<ComponentRenderable>(ResourceManager::GetPrimitive("Plane"), gridPipeline);
        auto& gridTransform = e.AddComponent<ComponentTransform>();
        gridTransform.Scale = glm::vec3(10.f);
        e.AddComponent<ComponentInternal>();

        // DEFAULT PIPELINE
        auto defaultShader = ResourceManager::GetOrLoadShader(Path(ResourceManager::GetIO()->GetCurrentDir().PathString + "\\resources\\raw\\shaders\\singleColor\\singleColor.glsl", PathType::File));
        PipelineSpecification defaultPipelineSpec;
        defaultPipelineSpec.Shader = defaultShader;
        defaultPipelineSpec.DebugName = "Default Pipeline";
        auto defaultPipeline = Pipeline::Create(defaultPipelineSpec);
        m_Scene->AddPipeline(defaultPipeline);
        m_Scene->SetDefaultPipeline(defaultPipeline);
    }

    void OnDetach() {}


    void OnUpdate(Timestep ts) {
        totalTime += ts;
        m_Camera->Update(ts);
    }


    void OnPreRender() {

        m_Framebuffer->Bind();

        RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        RenderCommand::Clear();

        // Clear our entity ID attachment to -1
        m_Framebuffer->ClearAttachment(1, -1);

        if (FramebufferSpecification spec = m_Framebuffer->GetSpecification();
            m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f && // zero sized framebuffer is invalid
            (spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y))
        {
            m_Framebuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
        }
    }
    void OnPostRender() {
        auto [mx, my] = ImGui::GetMousePos();
        mx -= m_ViewportBounds[0].x;
        my -= m_ViewportBounds[0].y;
        glm::vec2 viewportSize = m_ViewportBounds[1] - m_ViewportBounds[0];
        my = viewportSize.y - my;
        int mouseX = (int)mx;
        int mouseY = (int)my;

        if (mouseX >= 0 && mouseY >= 0 && mouseX < (int)viewportSize.x && mouseY < (int)viewportSize.y)
        {
            int pixelData = m_Framebuffer->ReadPixel(1, mouseX, mouseY);
            m_HoveredEntity = pixelData == -1 ? Entity() : Entity((entt::entity)pixelData, m_Scene.get());

            if (ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
                m_SceneHierarchy->SetSelectedEntity(m_HoveredEntity);
            }
        }
        m_Framebuffer->Unbind();
    }
    void OnRender() {
        if (m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f) {
            auto& window = Application::Get().GetWindow();
            glm::mat4 projection = glm::perspective(glm::radians(45.f), (float)m_ViewportSize.x / (float)m_ViewportSize.y, 0.1f, 100.0f);
            Application::Get().SetViewportSize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
        }
    }

    void OnRenderOverlay()
    {
        ImGui::DockSpaceOverViewport();

        ImGui::Begin("Viewport");

        auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
        auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
        auto viewportOffset = ImGui::GetWindowPos();
        m_ViewportBounds[0] = { viewportMinRegion.x + viewportOffset.x, viewportMinRegion.y + viewportOffset.y };
        m_ViewportBounds[1] = { viewportMaxRegion.x + viewportOffset.x, viewportMaxRegion.y + viewportOffset.y };

        m_ViewportFocused = ImGui::IsWindowFocused();
        m_ViewportHovered = ImGui::IsWindowHovered();
        ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
        m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };

        ImGui::Image((void*)m_Framebuffer->GetColorAttachmentRendererID(), ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

        if (ImGui::BeginDragDropTarget()) {
            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM")) {
                auto path = Path((const char*)payload->Data, PathType::File);

                if (path.FileEnding == "obj") {
                    auto id = ResourceManager::GetOrLoadModel(path);

                    auto e2 = m_Scene->CreateEntity();
                    e2.AddComponent<ComponentID>();
                    e2.AddComponent<ComponentRenderable>(id, m_Scene->GetDefaultPipeline());
                    e2.AddComponent<ComponentTag>("Backpack");
                    e2.AddComponent<ComponentTransform>();
                }
                else if (path.FileEnding == "simix") {
                    auto s = SceneSerializer(m_Scene);
                    s.Deserialize(path);
                }

                ImGui::EndDragDropTarget();
            }
        }

        // Gizmos
        ImGuizmo::Enable(true);
        ImGuizmo::SetOrthographic(false);
        ImGuizmo::SetDrawlist();
        ImGuizmo::SetRect(m_ViewportBounds[0].x, m_ViewportBounds[0].y, m_ViewportBounds[1].x - m_ViewportBounds[0].x, m_ViewportBounds[1].y - m_ViewportBounds[0].y);

        auto selectedEntity = m_SceneHierarchy->GetSelectedEntity();
        if (selectedEntity) {
            auto& tc = selectedEntity.GetComponent<ComponentTransform>();
            glm::mat4 transform = tc.GetTransform();

            bool snap = Input::IsKeyPressed(Key::LeftControl);
            float snapValue = 0.5f; // Snap to 0.5m for translation/scale
            // Snap to 45 degrees for rotation
            if (m_Toolbar->GetTranslationMode() == ImGuizmo::OPERATION::ROTATE)
                snapValue = 45.0f;

            float snapValues[3] = { snapValue, snapValue, snapValue };

            ImGuizmo::Manipulate(glm::value_ptr(Application::Get().GetSceneRenderer()->GetViewMatrix()), glm::value_ptr(Application::Get().GetSceneRenderer()->GetProjectionMatrix()),
                m_Toolbar->GetTranslationMode(), ImGuizmo::LOCAL, glm::value_ptr(transform),
                nullptr, snap ? snapValues : nullptr);
            if (ImGuizmo::IsUsing())
            {
                if (m_Action == nullptr)
                    m_Action = CreateRef<ActionTransform>(selectedEntity);

                if (ImGui::IsMouseClicked(ImGuiMouseButton_Right)) {
                    m_Action->Cancel();
                    ImGuizmo::Enable(false);
                }
                else {
                    glm::vec3 translation, rotation, scale;
                    Math::DecomposeTransform(transform, translation, rotation, scale);

                    glm::vec3 deltaRotation = rotation - tc.Rotation;
                    tc.Translation = translation;
                    tc.Rotation += deltaRotation;
                    tc.Scale = scale;
                }
            }
            else {
                if (m_Action != nullptr) {
                    auto m_ActionCast = (ActionTransform*)m_Action.get();

                    CommandStack::PushCommand(CreateRef<CommandTransform>(selectedEntity, m_ActionCast->GetLocation(), tc.Translation, m_ActionCast->GetRotation(), tc.Rotation, m_ActionCast->GetScale(), tc.Scale));
                    m_Action = nullptr;
                }
            }
        }

        if (m_Toolbar->GetShowGrid())
            ImGuizmo::DrawGrid(glm::value_ptr(Application::Get().GetSceneRenderer()->GetViewMatrix()), glm::value_ptr(Application::Get().GetSceneRenderer()->GetProjectionMatrix()), glm::value_ptr(glm::mat4(1.0)), 100.f);

        ImGui::End();
;

        m_MainMenu->Render();

        //m_ShaderEditor->Render();
        m_SceneHierarchy->Render();
        m_ContentBrowser->Render();
        m_Toolbar->Render();
    }

    void OnEvent(Event& e) {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<KeyPressedEvent>(SIMIX_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));
        dispatcher.Dispatch<KeyReleasedEvent>(SIMIX_BIND_EVENT_FN(ExampleLayer::OnKeyReleasedEvent));
    }

    bool OnKeyPressedEvent(KeyPressedEvent& e) {
        return m_ToggleUtil->OnKeyPressed(e);
    }
    bool OnKeyReleasedEvent(KeyReleasedEvent& e) {
        return m_Toolbar->OnKeyReleasedEvent(e);
    }
private:
    float totalTime = 0.f;
    Simulatrix::UUID m_ShaderID1;
    Simulatrix::UUID m_ShaderID2;
    Ref<ProjectionCamera> m_Camera;
    Ref<Framebuffer> m_Framebuffer;
    Ref<SceneHierarchy> m_SceneHierarchy;
    Ref<ContentBrowser> m_ContentBrowser;
    Ref<ShaderEditor> m_ShaderEditor;
    Ref<MainMenu> m_MainMenu;
    Ref<Toolbar> m_Toolbar;
    Ref<ToggleUtil> m_ToggleUtil;
    Ref<IconLibrary> m_IconLib;
    Ref<Action> m_Action;
    Ref<Scene> m_Scene;
    Entity m_HoveredEntity;
    bool m_ViewportFocused = false, m_ViewportHovered = false;
    glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
    glm::vec2 m_ViewportBounds[2];

};

class Sandbox : public Simulatrix::Application
{
public:
    Sandbox() {
        PushLayer(new ExampleLayer(Application::Get().GetActiveScene()));
    }

    ~Sandbox() {

    }
};

Simulatrix::Application* Simulatrix::CreateApplication() {
    return new Sandbox();
}
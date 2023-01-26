#include "simixpch.h"
#include "MainMenu.h"
#include <ImGui/imgui.h>
#include <ImGui/imgui_internal.h>
#include "Simulatrix/ResourceManager/ResourceManager.h"
#include "Simulatrix/Core/Core.h"
#include <Simulatrix/Scene/SceneSerializer.h>
#include "../CommandStack/CommandStack.h"
namespace Simulatrix {
    void MainMenu::Render() {
        ImGui::BeginMainMenuBar();

        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Save", "CTRL+S")) {
                Save();
            }

            if (ImGui::MenuItem("Open", "CTRL+O")) {
                Load();
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Undo", "CTRL+Z", false, CommandStack::CanUndo())) {
                Undo();
            }
            if (ImGui::MenuItem("Redo", "CTRL+Y", false, CommandStack::CanRedo())) {
                Redo();
            }

            /*ImGui::Separator();
            if (ImGui::MenuItem("Cut", "CTRL+X")) {}
            if (ImGui::MenuItem("Copy", "CTRL+C")) {}
            if (ImGui::MenuItem("Paste", "CTRL+V")) {}*/
            ImGui::EndMenu();
        }

        if (ImGui::IsKeyReleased(ImGuiKey_Z) && ImGui::IsKeyDown(ImGuiKey_LeftCtrl) && CommandStack::CanUndo()) {
            Undo();
        }
        if (ImGui::IsKeyReleased(ImGuiKey_Y) && ImGui::IsKeyDown(ImGuiKey_LeftCtrl) && CommandStack::CanRedo()) {
            Redo();
        }

        if (ImGui::IsKeyReleased(ImGuiKey_S) && ImGui::IsKeyDown(ImGuiKey_LeftCtrl)) {
            Save();
        }
        if (ImGui::IsKeyReleased(ImGuiKey_O) && ImGui::IsKeyDown(ImGuiKey_LeftCtrl)) {
            Load();
        }

        ImGui::EndMainMenuBar();
    }
    void MainMenu::Undo() {
        CommandStack::Undo();
    }
    void MainMenu::Redo() {
        CommandStack::Redo();
    }
    void MainMenu::Save() {
        auto path = ResourceManager::GetIO()->SaveFile("");
        if (path.PathString != "") {
            auto serializer = SceneSerializer(m_Scene);
            serializer.Serialize(path);
        }
    }
    void MainMenu::Load() {
        auto path = ResourceManager::GetIO()->OpenFile("");
        if (path.PathString != "") {
            auto serializer = SceneSerializer(m_Scene);
            serializer.Deserialize(path);
        }
    }

    void MainMenu::SetScene(const Ref<Scene>& scene)
    {
        m_Scene = scene;
    }
}
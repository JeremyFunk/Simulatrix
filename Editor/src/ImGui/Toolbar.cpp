#include "simixpch.h"
#include "Toolbar.h"
#include "Simulatrix/ResourceManager/ResourceManager.h"
#include <Simulatrix/Util/StringUtil.h>
#include <Simulatrix/ImGui/Components/ImGuiButtonBar.h>

namespace Simulatrix {
    void Toolbar::Render() {
        ImGuiWindowFlags window_flags = 0;
        window_flags |= ImGuiWindowFlags_NoBackground;
        window_flags |= ImGuiWindowFlags_NoTitleBar;
        // etc.
        ImGui::Begin("Toolbar", 0, window_flags);

        std::vector<void*> buttons;
        buttons.push_back(m_IconLibrary->GetImGuiIconByName("move"));
        buttons.push_back(m_IconLibrary->GetImGuiIconByName("scale"));
        buttons.push_back(m_IconLibrary->GetImGuiIconByName("rotate"));
        buttons.push_back(m_IconLibrary->GetImGuiIconByName("model-edit"));

        int selected = m_TranslationMode == ImGuizmo::OPERATION::TRANSLATE ? 0 : 
            m_TranslationMode == ImGuizmo::OPERATION::SCALE ? 1 :
            m_TranslationMode == ImGuizmo::OPERATION::ROTATE ? 2 : 3;


        switch (DisplayImageButtonBar(buttons, ImVec2(16, 16), selected)) {
            case 0:
                m_TranslationMode = ImGuizmo::OPERATION::TRANSLATE;
                break;
            case 1:
                m_TranslationMode = ImGuizmo::OPERATION::SCALE;
                break;
            case 2:
                m_TranslationMode = ImGuizmo::OPERATION::ROTATE;
                break;
            case 3:
                m_TranslationMode = ImGuizmo::OPERATION::UNIVERSAL;
                break;
        }
        ImGui::SameLine();

        if (ImGui::ImageButton(m_IconLibrary->GetImGuiIconByName("grid"), ImVec2(16, 16), ImVec2(0, 0), ImVec2(1, 1), -1, ImVec4(0, 0, 0, 0), ImVec4(1, 1, 1, m_ShowGrid ? 1 : 0.5))) {
            m_ShowGrid = !m_ShowGrid;
        }
        
        ImGui::SetNextItemWidth(20.f);

        if (ImGui::BeginMenu("Add Mesh")) {

            for (auto primitive : PrimitiveLibrary::GetNames())
            {
                if (ImGui::Selectable(primitive.c_str())) {
                    m_Scene->InstantiatePrimitive(primitive);
                }
            } 

            ImGui::EndMenu();
        }

        ImGui::End();
    }
}
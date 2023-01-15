#include <simixpch.h>
#include "ImGuiEditor.h"
#include "Simulatrix/Renderer/Framebuffer.h"
#include <imgui.h>
#include "Simulatrix/Core/Application.h"

ImGuiEditor::ImGuiEditor() : Layer("EditorLayer") {
}
void ImGuiEditor::OnAttach()
{
}

void ImGuiEditor::OnDetach()
{

}

void ImGuiEditor::OnRenderOverlay()
{
    ImGui::DockSpaceOverViewport();
    ImGui::Begin("AHA");
    ImGui::Text("LOLO");
    ImGui::End();

    ImGui::Begin("Viewport");
    auto viewportSize = ImGui::GetContentRegionAvail();
    ImGui::Image((void*)Application::Get().GetFramebuffer()->GetColorAttachmentRendererID(), ImVec2(viewportSize.x, viewportSize.y), ImVec2(0, 1), ImVec2(1, 0));

    
}

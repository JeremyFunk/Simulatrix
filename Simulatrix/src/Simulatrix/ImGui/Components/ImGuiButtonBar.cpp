#include "simixpch.h"
#include <imgui.h>
#include "ImGuiButtonBar.h"

namespace Simulatrix {
    int DisplayImageButtonBar(std::vector<void*> buttons, ImVec2 size, int selected) {
        int clicked = -1;
        for (int i = 0; i < buttons.size(); i++) {
            if (i != 0) {
                ImGui::SameLine();
            }
            if (i != selected) {
                if (ImGui::ImageButton(buttons[i], size, ImVec2(0, 0), ImVec2(1, 1), -1, ImVec4(0.0, 0.0, 0.0, 0.0), ImVec4(1.0, 1.0, 1.0, 0.5))) {
                    clicked = i;
                }
            }
            else if (ImGui::ImageButton(buttons[i], size)) {
                clicked = i;
            }
        }
        return clicked;
    }
}
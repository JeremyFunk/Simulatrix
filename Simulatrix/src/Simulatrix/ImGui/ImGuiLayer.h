#pragma once

#include "Simulatrix/Core/Layer.h"

namespace Simulatrix {

    class ImGuiLayer : public Layer {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void OnAttach();
        void OnDetach();
        void OnUpdate(Timestep ts);
        void OnRenderOverlay();

        void Begin();
        void End();

        void OnEvent(Event& e);
        void SetDarkThemeColors();
    };
}
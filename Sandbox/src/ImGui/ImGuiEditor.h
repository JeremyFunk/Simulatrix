#pragma once
#include <Simulatrix/Core/Layer.h>
#include <Simulatrix/Renderer/Framebuffer.h>

using namespace Simulatrix;
class ImGuiEditor : public Simulatrix::Layer {
public:
    ImGuiEditor();
    

    void OnAttach() override;
    void OnDetach() override;
    void OnRenderOverlay() override;
private:
};

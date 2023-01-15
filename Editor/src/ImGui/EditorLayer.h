#pragma once
#include <Simulatrix/Core/Layer.h>
#include <Simulatrix/Renderer/Framebuffer.h>

using namespace Simulatrix;
class EditorLayer : public Simulatrix::Layer {
public:
    EditorLayer();
    

    void OnDetach() override;
private:
};

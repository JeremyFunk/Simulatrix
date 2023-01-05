#pragma once
#include "Simulatrix/Renderer/RendererAPI.h"
namespace Simulatrix {
    class OpenGLRendererAPI : public RendererAPI {
        virtual void Clear() override;
        virtual void SetClearColor(const glm::vec4& color) override;

        virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
    };
}
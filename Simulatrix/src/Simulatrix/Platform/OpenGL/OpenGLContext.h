#pragma once
#include <Simulatrix/Renderer/GraphicsContext.h>
struct GLFWwindow;
namespace Simulatrix {
    class OpenGLContext : public GraphicsContext
    {
    public:
        OpenGLContext(GLFWwindow* windowHandle);

        void Init() override;
        void SwapBuffers() override;
    private:
        GLFWwindow* m_WindowHandle;
    };
}


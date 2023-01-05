#include "simixpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <Simulatrix/Core/Core.h>
#include <Simulatrix/Debug/Log.h>

namespace Simulatrix {
    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle)
    {
        SIMIX_CORE_ASSERT(windowHandle, "Window handle is null!");
    }
    void OpenGLContext::Init()
    {
        glfwMakeContextCurrent(m_WindowHandle);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        SIMIX_CORE_ASSERT(success, "Failed to initialize Glad!");
    }
    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(m_WindowHandle);
    }
}
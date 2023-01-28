#include "simixpch.h"
#include "OpenGLPipeline.h"

namespace Simulatrix {
    void OpenGLPipeline::Invalidate()
    {
        
    }

    void OpenGLPipeline::Bind()
    {
        m_Specs.Shader->Bind();
    }
}
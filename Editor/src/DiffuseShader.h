#pragma once

//#include "Simulatrix.h"
//#include "Simulatrix/Core/ShaderImplementation.h"
//#include "Simulatrix/Scene/Components.h"
//
//namespace Simulatrix {
//    class DiffuseShader : public ShaderImplementation<ComponentTextureMaterial> {
//    public:
//        DiffuseShader(Path& vs, Path& fs) : ShaderImplementation<ComponentTextureMaterial>(vs, fs, "Diffuse Shader", ShaderUniforms({
//            { ShaderDataType::Int, "u_textureDiffuse" },
//            { ShaderDataType::Mat4, "u_viewMatrix" },
//            { ShaderDataType::Mat4, "u_projectionMatrix" },
//            { ShaderDataType::Mat4, "u_modelMatrix" }
//        })) 
//        {
//
//        }
//
//        template<typename F = ComponentTextureMaterial>
//        void LoadUniformsImpl(F material) override {
//            m_Shader->SetUniform("u_textureDiffuse", material.Diffuse->GetRendererID());
//        }
//    };
//}
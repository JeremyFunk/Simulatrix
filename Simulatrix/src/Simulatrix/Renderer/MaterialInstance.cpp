#include "simixpch.h"
#include "MaterialInstance.h"
#include "Simulatrix/Renderer/Renderer.h"
#include <Simulatrix/Core/Core.h>

namespace Simulatrix {
    void MaterialInstance::Bind(Ref<Shader> shader) {
        for (auto& element : MaterialInstance::m_BoolUniform) {
            shader->SetUniform(element.first.c_str(), element.second);
        }
        for (auto& element : MaterialInstance::m_FloatUniform) {
            shader->SetUniform(element.first.c_str(), element.second);
        }
        for (auto& element : MaterialInstance::m_IntUniform) {
            shader->SetUniform(element.first.c_str(), element.second);
        }
        for (auto& element : MaterialInstance::m_Vec2Uniform) {
            shader->SetUniform(element.first.c_str(), element.second);
        }
        for (auto& element : MaterialInstance::m_Vec3Uniform) {
            shader->SetUniform(element.first.c_str(), element.second);
        }
        for (auto& element : MaterialInstance::m_Vec4Uniform) {
            shader->SetUniform(element.first.c_str(), element.second);
        }
        for (auto& element : MaterialInstance::m_Mat3Uniform) {
            shader->SetUniform(element.first.c_str(), element.second);
        }
        for (auto& element : MaterialInstance::m_Mat4Uniform) {
            shader->SetUniform(element.first.c_str(), element.second);
        }
        for (auto& element : MaterialInstance::m_IVec2Uniform) {
            shader->SetUniform(element.first.c_str(), element.second);
        }
        for (auto& element : MaterialInstance::m_IVec3Uniform) {
            shader->SetUniform(element.first.c_str(), element.second);
        }
        for (auto& element : MaterialInstance::m_IVec4Uniform) {
            shader->SetUniform(element.first.c_str(), element.second);
        }
        for (auto& element : MaterialInstance::m_UIntUniform) {
            shader->SetUniform(element.first.c_str(), element.second);
        }
    }
}
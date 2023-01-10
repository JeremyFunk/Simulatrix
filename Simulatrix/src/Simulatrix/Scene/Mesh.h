#pragma once
#include <glm/glm.hpp>
namespace Simulatrix {
    struct ComponentMesh {
        uint32_t RendererID;
        ComponentMesh() = default;
        ComponentMesh(uint32_t RendererID) : RendererID(RendererID)
        {

        }
    };
    struct ComponentTransform {
        glm::mat4 Transform;
        ComponentTransform() = default;
        ComponentTransform(glm::mat4 Transform) : Transform(Transform)
        {

        }
    };
    struct ComponentMaterial {
        glm::vec3 Color;
        ComponentMaterial() = default;
        ComponentMaterial(glm::vec3 Color) : Color(Color)
        {

        }
    };
    struct ComponentShader {
        uint32_t RendererID;
        ComponentShader() = default;
        ComponentShader(uint32_t RendererID) : RendererID(RendererID)
        {

        }
    };
}
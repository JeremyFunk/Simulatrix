#pragma once
#include <glm/glm.hpp>
#include "Simulatrix/Core/UUID.h"
namespace Simulatrix {
    struct IDComponent {
        UUID ID;

        IDComponent() = default;
        IDComponent(const IDComponent&) = default;
        IDComponent(const UUID& id) : ID(id) {}
    };

    struct TagComponent {
        std::string Tag;

        TagComponent() = default;
        TagComponent(const TagComponent&) = default;
        TagComponent(const std::string& tag) : Tag(tag) {}
    };

    struct ComponentMesh {
        uint32_t RendererID;
        ComponentMesh() = default;
        ComponentMesh(uint32_t RendererID) : RendererID(RendererID)
        {

        }
    };
    struct ComponentModel {
        uint32_t ModelID;
        ComponentModel() = default;
        ComponentModel(uint32_t ModelID) : ModelID(ModelID)
        {

        }
    };
    struct ComponentTexture {
        uint32_t RendererID;
        ComponentTexture() = default;
        ComponentTexture(uint32_t RendererID) : RendererID(RendererID)
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
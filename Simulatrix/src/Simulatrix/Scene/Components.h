#pragma once
#include <glm/glm.hpp>
#include "Simulatrix/Core/UUID.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
namespace Simulatrix {
    struct ComponentID {
        UUID ID;

        ComponentID() = default;
        ComponentID(const ComponentID&) = default;
        ComponentID(const UUID& id) : ID(id) {}
    };

    struct ComponentTag {
        std::string Tag;

        ComponentTag() = default;
        ComponentTag(const ComponentTag&) = default;
        ComponentTag(const std::string& tag) : Tag(tag) {}
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
        glm::vec3 Translation = { 0.0f, 0.0f, 0.0f };
        glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f };
        glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };
        ComponentTransform() = default;
        ComponentTransform(const glm::vec3& translation) : Translation(translation)
        {

        }

        glm::mat4 GetTransform() const
        {
            glm::mat4 rotation = glm::toMat4(glm::quat(Rotation));

            return glm::translate(glm::mat4(1.0f), Translation)
                * rotation
                * glm::scale(glm::mat4(1.0f), Scale);
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
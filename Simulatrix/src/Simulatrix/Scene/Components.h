#pragma once
#include <glm/glm.hpp>
#include "Simulatrix/Core/UUID.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include "Simulatrix/Core/Core.h"
#include <Simulatrix/Renderer/Texture.h>
#include <Simulatrix/Renderer/Shader.h>
#include <Simulatrix/Renderer/Pipeline.h>
#include <Simulatrix/Scene/SceneData.h>
#include <Simulatrix/Scene/MaterialFactory.h>

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

    /*struct ComponentMesh {
        UUID ID;
        ComponentMesh() = default;
        ComponentMesh(UUID ID) : ID(ID)
        {

        }
    };*/
    struct ComponentInternal {
        bool Serialize = false;
        ComponentInternal() = default;
    };

    struct ExtraComponentRenderData {

    };

    struct ComponentRenderable {
        Ref<SceneModel> Model;
        Ref<Pipeline> RenderPipeline;
        // TODO add material here aswell
        ComponentRenderable() = default;
        ComponentRenderable(Ref<SceneModel> model, Ref<Pipeline> pipeline) : Model(model), RenderPipeline(pipeline)
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
        Ref<MaterialInstance> Material;
        ComponentMaterial() = default;
        ComponentMaterial(Ref<MaterialInstance> material) : Material(material)
        {

        }
    };
    /*struct ComponentTextureMaterial {
        Ref<Texture2D> Diffuse;
        ComponentTextureMaterial() = default;
        ComponentTextureMaterial(Ref<Texture2D> diffuse) : Diffuse(diffuse)
        {
        }
    };*/
}
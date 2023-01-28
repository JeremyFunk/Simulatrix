#pragma once
#include "entt.hpp"
#include "Components.h"
#include "Simulatrix/Core/Core.h"
#include "Simulatrix/Renderer/Shader.h"
#include "Entity.h"
#include <Simulatrix/Core/Camera.h>
#include "Simulatrix/ResourceManager/ResourceManager.h"
#include "reactphysics3d/reactphysics3d.h"
namespace Simulatrix {

    class Scene {
    public:
        Scene();
        ~Scene();

        Entity CreateEntity() {
            return Entity(m_Registry.create(), this);
        }

        Entity CreateEntityWithUUID(UUID& uuid) {
            auto e = Entity(m_Registry.create(), this);
            e.AddComponent<ComponentID>(uuid);
            return e;
        }

        template<typename... Components>
        auto GetAllEntitiesWith()
        {
            return m_Registry.view<Components...>();
        }

        template<typename... Components>
        bool HasComponents(entt::entity e)
        {
            return m_Registry.all_of<Components...>(e);
        }

        template<typename... Components>
        auto GetComponents(entt::entity e) {
            //SIMIX_CORE_ASSERT(e.HasComponents<Components...>(), "Entity does not have components!");
            return m_Registry.get<Components...>(e);
        }

        template<typename T>
        auto GetComponent(entt::entity e) {
            //SIMIX_CORE_ASSERT(e.HasComponent<T>(), "Entity does not have component!");
            return m_Registry.get<T>(e);
        }

        template<typename T>
        auto ReplaceComponent(entt::entity e, T component) {
            //SIMIX_CORE_ASSERT(e.HasComponent<T>(), "Entity does not have component!");

            return m_Registry.replace<T>(e, component);
        }

        Ref<Camera> GetCamera() {
            return m_Camera;
        }
        void SetCamera(Ref<Camera> cam) {
            m_Camera = cam;
        }
        void AddShader(Ref<Shader> shader) {
            m_Shaders.push_back(shader);
        }
        Ref<Shader> GetShader(std::string name) {
            for (auto shader : m_Shaders) {
                if (shader->GetName() == name) {
                    return shader;
                }
            }
            return nullptr;
        }
        const std::vector<Ref<Shader>> GetShaders() {
            return m_Shaders;
        }

        Entity InstantiatePrimitive(std::string name) {
            auto e = CreateEntity();
            e.AddComponent<ComponentRenderable>(ResourceManager::GetPrimitive(name), m_DefaultPipeline);
            e.AddComponent<ComponentTag>(name);
            e.AddComponent<ComponentID>();
            e.AddComponent<ComponentTransform>();
            return e;
        }

        const std::vector<Ref<Pipeline>> GetPipelines() {
            return m_Pipelines;
        }
        
        void AddPipeline(Ref<Pipeline> pipeline) {
            m_Pipelines.push_back(pipeline);
        }

        Ref<Pipeline> GetPipeline(UUID id) {
            for (auto pipeline : m_Pipelines) {
                if (pipeline->GetID() == id) {
                    return pipeline;
                }
            }
            return nullptr;
        }

        void SetDefaultPipeline(Ref<Pipeline> pipeline) {
            m_DefaultPipeline = pipeline;
        }

        Ref<Pipeline> GetDefaultPipeline() {
            return m_DefaultPipeline;
        }
    private:
        Ref<Camera> m_Camera;
        std::vector<Ref<Shader>> m_Shaders;
        Ref<Pipeline> m_DefaultPipeline;
        std::vector<Ref<Pipeline>> m_Pipelines;

        Ref<reactphysics3d::PhysicsCommon> m_PhysicsCommon;
        reactphysics3d::PhysicsWorld* m_PhysicsWorld;
        entt::registry m_Registry;
        friend class Entity;
        friend class SceneSerializer;
        friend class SceneHierarchy;
        friend class SceneRenderer;
    };
    
}
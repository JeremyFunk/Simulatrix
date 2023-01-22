#pragma once
#include "entt.hpp"
#include "Components.h"
#include "Simulatrix/Core/Core.h"
#include "Simulatrix/Renderer/Shader.h"
#include "Entity.h"
#include <Simulatrix/Core/Camera.h>
#include "Simulatrix/Renderer/ShaderImplementation.h"
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

        void FileDropped(Path& path);
    private:
        Ref<Camera> m_Camera;
        std::vector<Ref<Shader>> m_Shaders;

        entt::registry m_Registry;
        friend class Entity;
        friend class SceneSerializer;
        friend class SceneHierarchy;
    };
    
}
#pragma once
#include "entt.hpp"
#include "Mesh.h"
#include "Simulatrix/Core/Core.h"
#include "Simulatrix/Renderer/Shader.h"
#include "Entity.h"
namespace Simulatrix {
    class Scene {
    public:
        Scene();
        ~Scene();

        Entity CreateEntity() {
            return Entity(m_Registry.create(), this);
        }

        template<typename... Components>
        auto GetAllEntitiesWith()
        {
            return m_Registry.view<Components...>();
        }

        template<typename... Components>
        auto HasComponents()
        {
            return m_Registry.all_of<Components...>();
        }

        template<typename... Components>
        auto GetComponents(entt::entity e) {
            SIMIX_CORE_ASSERT(HasComponents<Components>(), "Entity does not have components!");

            return m_Registry.get<Components...>(e);
        }

        template<typename T>
        auto GetComponent(entt::entity e) {
            SIMIX_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");

            return m_Registry.get<T>(e);
        }

        template<typename T>
        auto ReplaceComponent(entt::entity e, T component) {
            SIMIX_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");

            return m_Registry.replace<T>(e, component);
        }
    private:
        entt::registry m_Registry;
        friend class Entity;
    };
    
}
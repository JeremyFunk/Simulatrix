#pragma once
#include "entt.hpp"
#include "Simulatrix/Scene/Scene.h"
#include "Simulatrix/Core/UUID.h"
#include "Simulatrix/Scene/Components.h"
namespace Simulatrix {
    class Scene;
    class Entity {
    public:

        Entity() = default;
        Entity(entt::entity e, Scene* scene) : m_Entity(e), m_Scene(scene) {

        }

        UUID GetUUID() { return GetComponent<IDComponent>().ID; }

        template<typename T>
        bool HasComponent() {
            return HasComponents<T>();
        }

        template<typename... Components>
        bool HasComponents() {
            return m_Scene->m_Registry.any_of<Components...>(m_Entity);
        }

        template<typename T, typename... Args>
        T& AddComponent(Args&&... args) {
            SIMIX_CORE_ASSERT(!HasComponent<T>(), "Entity already has component!");
            
            return m_Scene->m_Registry.emplace<T>(m_Entity, std::forward<Args>(args)...);
        }

        template<typename T>
        T& GetComponent() {
            SIMIX_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");

            return m_Scene->m_Registry.get<T>(m_Entity);
        }

        template<typename... Components>
        auto GetComponents() {
            SIMIX_CORE_ASSERT(HasComponents<Components...>(), "Entity does not have components!");

            return m_Scene->m_Registry.get<Components...>(m_Entity);
        }

        template<typename T>
        void RemoveComponent() {
            SIMIX_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");

            return m_Scene->m_Registry.remove<T>(m_Entity);
        }
    private:
        entt::entity m_Entity;
        Scene* m_Scene;
    };
}
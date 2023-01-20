#pragma once
#include "Simulatrix/Core/UUID.h"
#include "Simulatrix/Core/Core.h"

namespace Simulatrix {
    template <typename T>
    class IdentifierMap {

        std::vector<T>::iterator begin() { return m_Layers.begin(); }
        std::vector<T>::iterator end() { return m_Layers.end(); }

        void emplace(std::string name, UUID id, T element) 
        { 
            m_ElementsString.emplace(name, element);
            m_ElementsUUID.emplace(id, element);
            m_ElementsString.
        }

        bool contains(std::string name) {
            return m_ElementsString.find(name) != m_ElementsString.end();
        }
        bool contains(UUID id) {
            return m_ElementsUUID.find(id) != m_ElementsUUID.end();
        }

        T find(std::string name) {
            return m_ElementsString.find(name);
        }
        T find(UUID id) {
            return m_ElementsUUID.find(id);
        }

        void clear() {
            m_ElementsString.clear();
            m_ElementsUUID.clear();
        }
    private:
        std::unordered_map<std::string, T> m_ElementsString;
        std::unordered_map<UUID, T> m_ElementsUUID;
    };
}
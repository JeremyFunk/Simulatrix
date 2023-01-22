#pragma once
#include "Simulatrix/Core/UUID.h"
#include "Simulatrix/Core/Core.h"

namespace Simulatrix {
    template <typename T>
    class IdentifierMap {
    public:
        typename std::vector<T>::iterator begin() { 
            return m_Elements.begin(); 
        }
        typename std::vector<T>::iterator end() {
            return m_Elements.end(); 
        }

        void emplace(std::string name, UUID id, T element) 
        { 
            m_Names.push_back(name);
            m_UUIDs.push_back(id);
            m_Elements.push_back(element);
        }

        bool contains(std::string name) {
            for (auto& n : m_Names) {
                if (n == name)
                    return true;
            }
            return false;
        }
        bool contains(UUID id) {
            for (auto& n : m_UUIDs) {
                if (n == id)
                    return true;
            }
            return false;
        }

        std::string getName(UUID id) {
            for (int i = 0; i < m_UUIDs.size(); i++) {
                if (m_UUIDs[i] == id)
                    return m_Names[i];
            }
        }
        UUID getUUID(std::string name) {
            for (int i = 0; i < m_Names.size(); i++) {
                if (m_Names[i] == name)
                    return m_UUIDs[i];
            }
        }

        T find(std::string name) {
            for (int i = 0; i < m_Names.size(); i++) {
                if (m_Names[i] == name)
                    return m_Elements[i];
            }
        }
        T find(UUID id) {
            for (int i = 0; i < m_UUIDs.size(); i++) {
                if (m_UUIDs[i] == id)
                    return m_Elements[i];
            }
        }

        std::vector<std::string> getNames() {
            return m_Names;
        }
        std::vector<UUID> getUUIDs() {
            return m_UUIDs;
        }
        std::vector<T> getElements() {
            return m_Elements;
        }

        void clear() {
            m_Names.clear();
            m_UUIDs.clear();
            m_Elements.clear();
        }

        T operator[](std::string name) {
            return find(name);
        }
        T operator[](UUID id) {
            return find(id);
        }
    private:
        std::vector<std::string> m_Names;
        std::vector<UUID> m_UUIDs;
        std::vector<T> m_Elements;
    };
}
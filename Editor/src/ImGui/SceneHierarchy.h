#pragma once
#include "Simulatrix/Core/Core.h"
#include "Simulatrix/Scene/Scene.h"
#include "IconLibrary.h"
namespace Simulatrix {
    class SceneHierarchy {
    public:
        SceneHierarchy(Ref<Scene> scene, Ref<IconLibrary> iconLibrary) : m_Scene(scene), m_IconLibrary(iconLibrary) {
        }
        void Render();
        void SetScene(const Ref<Scene>& scene);

        Entity GetSelectedEntity() const { return m_SelectionContext; }
        void SetSelectedEntity(Entity entity);
    private:
        template<typename T>
        void DisplayAddComponentEntry(const std::string& entryName);
        void DrawComponents(Entity entity);
        void DrawEntityNode(Entity entity);
    private:
        Ref<Scene> m_Scene;
        Entity m_SelectionContext;
        Ref<IconLibrary> m_IconLibrary;
    };
}
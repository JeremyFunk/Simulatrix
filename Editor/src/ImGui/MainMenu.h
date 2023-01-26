#pragma once
#include "Simulatrix/Core/Core.h"
#include "Simulatrix/Scene/Scene.h"
#include "IconLibrary.h"
namespace Simulatrix {
    class MainMenu {

    public:
        MainMenu(Ref<Scene> scene, Ref<IconLibrary> iconLibrary) : m_Scene(scene), m_IconLibrary(iconLibrary) {
        }
        void Render();
        void SetScene(const Ref<Scene>& scene);
    private:
        void Undo();
        void Redo();
        void Save();
        void Load();
    private:
        Ref<Scene> m_Scene;
        Ref<IconLibrary> m_IconLibrary;
    };
}
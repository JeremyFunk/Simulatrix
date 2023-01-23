#pragma 
#include <ImGui/imgui.h>
#include "Simulatrix/Core/Core.h"
#include "Simulatrix/Scene/Scene.h"
#include "ImGuizmo.h"
#include "IconLibrary.h"
namespace Simulatrix {
    class Toolbar {
    public:
        Toolbar(Ref<Scene> scene, Ref<IconLibrary> iconLibrary) : m_Scene(scene), m_IconLibrary(iconLibrary), m_TranslationMode(ImGuizmo::OPERATION::UNIVERSAL) {}
        void Render();
        ImGuizmo::OPERATION GetTranslationMode() {
            return m_TranslationMode;
        }
        void SetTranslationMode(ImGuizmo::OPERATION op) {
            m_TranslationMode = op;
        }
        void SetScene(const Ref<Scene>& scene) {
            m_Scene = scene;
        }
        bool GetShowGrid() {
            return m_ShowGrid;
        }
    private:
        Ref<Scene> m_Scene;
        Ref<IconLibrary> m_IconLibrary;
        ImGuizmo::OPERATION m_TranslationMode;
        bool m_ShowGrid = true;
    };
}
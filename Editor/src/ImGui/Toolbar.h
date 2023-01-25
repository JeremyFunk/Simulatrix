#pragma 
#include <ImGui/imgui.h>
#include "Simulatrix/Core/Core.h"
#include "Simulatrix/Scene/Scene.h"
#include "ImGuizmo.h"
#include "IconLibrary.h"
#include "Simulatrix/Events/KeyEvent.h"
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


        bool OnKeyReleasedEvent(KeyReleasedEvent& e) {
            if (e.GetKeyCode() == Key::X) {
                if (m_TranslationMode == ImGuizmo::OPERATION::TRANSLATE_X) {
                    m_TranslationMode = ImGuizmo::OPERATION::TRANSLATE;
                }
                else if (IsTranslating()) {
                    m_TranslationMode = ImGuizmo::OPERATION::TRANSLATE_X;
                }
                else if (m_TranslationMode == ImGuizmo::OPERATION::SCALE_X) {
                    m_TranslationMode = ImGuizmo::OPERATION::SCALE;
                }
                else if (IsScaling()) {
                    m_TranslationMode = ImGuizmo::OPERATION::SCALE_X;
                }
                else if (m_TranslationMode == ImGuizmo::OPERATION::ROTATE_X) {
                    m_TranslationMode = ImGuizmo::OPERATION::ROTATE;
                }
                else if (IsRotating()) {
                    m_TranslationMode = ImGuizmo::OPERATION::ROTATE_X;
                }
            }
            else if (e.GetKeyCode() == Key::Y) {
                if (m_TranslationMode == ImGuizmo::OPERATION::TRANSLATE_Y) {
                    m_TranslationMode = ImGuizmo::OPERATION::TRANSLATE;
                }
                else if (IsTranslating()) {
                    m_TranslationMode = ImGuizmo::OPERATION::TRANSLATE_Y;
                }
                else if (m_TranslationMode == ImGuizmo::OPERATION::SCALE_Y) {
                    m_TranslationMode = ImGuizmo::OPERATION::SCALE;
                }
                else if (IsScaling()) {
                    m_TranslationMode = ImGuizmo::OPERATION::SCALE_Y;
                }
                else if (m_TranslationMode == ImGuizmo::OPERATION::ROTATE_Y) {
                    m_TranslationMode = ImGuizmo::OPERATION::ROTATE;
                }
                else if (IsRotating()) {
                    m_TranslationMode = ImGuizmo::OPERATION::ROTATE_Y;
                }
            }
            else if (e.GetKeyCode() == Key::Z) {
                if (m_TranslationMode == ImGuizmo::OPERATION::TRANSLATE_Z) {
                    m_TranslationMode = ImGuizmo::OPERATION::TRANSLATE;
                }
                else if (IsTranslating()) {
                    m_TranslationMode = ImGuizmo::OPERATION::TRANSLATE_Z;
                }
                else if (m_TranslationMode == ImGuizmo::OPERATION::SCALE_Z) {
                    m_TranslationMode = ImGuizmo::OPERATION::SCALE;
                }
                else if (IsScaling()) {
                    m_TranslationMode = ImGuizmo::OPERATION::SCALE_Z;
                }
                else if (m_TranslationMode == ImGuizmo::OPERATION::ROTATE_Z) {
                    m_TranslationMode = ImGuizmo::OPERATION::ROTATE;
                }
                else if (IsRotating()) {
                    m_TranslationMode = ImGuizmo::OPERATION::ROTATE_Z;
                }
            }
            return false;
        }

    private:
        bool IsTranslating() {
            return m_TranslationMode == ImGuizmo::OPERATION::TRANSLATE || m_TranslationMode == ImGuizmo::OPERATION::TRANSLATE_X || m_TranslationMode == ImGuizmo::OPERATION::TRANSLATE_Y || m_TranslationMode == ImGuizmo::OPERATION::TRANSLATE_Z;
        }
        bool IsScaling() {
            return m_TranslationMode == ImGuizmo::OPERATION::SCALE || m_TranslationMode == ImGuizmo::OPERATION::SCALE_X || m_TranslationMode == ImGuizmo::OPERATION::SCALE_Y || m_TranslationMode == ImGuizmo::OPERATION::TRANSLATE_Z;
        }
        bool IsRotating() {
            return m_TranslationMode == ImGuizmo::OPERATION::ROTATE || m_TranslationMode == ImGuizmo::OPERATION::ROTATE_X || m_TranslationMode == ImGuizmo::OPERATION::ROTATE_Y || m_TranslationMode == ImGuizmo::OPERATION::ROTATE_Z;
        }

        Ref<Scene> m_Scene;
        Ref<IconLibrary> m_IconLibrary;
        ImGuizmo::OPERATION m_TranslationMode;
        bool m_ShowGrid = true;
    };
}
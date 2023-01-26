#pragma once
#include "Simulatrix/Core/Core.h"
#include "Simulatrix/Scene/Scene.h"
#include "IconLibrary.h"
#include <imgui-node-editor/imgui_node_editor.h>

namespace ed = ax::NodeEditor;
namespace Simulatrix {
    struct LinkInfo
    {
        ed::LinkId Id;
        ed::PinId  InputId;
        ed::PinId  OutputId;
    };
    class ShaderEditor {

    public:
        ShaderEditor(Ref<Scene> scene, Ref<IconLibrary> iconLibrary);
        ~ShaderEditor();
        void Render();
        void SetScene(const Ref<Scene>& scene);
    private:
        Ref<Scene> m_Scene;
        Ref<IconLibrary> m_IconLibrary;
        ax::NodeEditor::EditorContext* m_Context;
        ImVector<LinkInfo>   m_Links;                // List of live links. It is dynamic unless you want to create read-only view over nodes.
        int                  m_NextLinkId = 100;     // Counter to help generate link ids. In real application this will probably based on pointer to user data structure.
    };
}
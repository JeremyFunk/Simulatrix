#pragma once
#include "Simulatrix/Core/Core.h"
#include "Simulatrix/Renderer/Texture.h"
namespace Simulatrix {
    class IconLibrary {
    public:
        Ref<Texture2D> LoadIconByName(std::string name);
        Ref<Texture2D> GetIconByName(std::string name);
    private:
        std::unordered_map<std::string, Ref<Texture2D>> m_Icons;
    };
}
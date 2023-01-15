#include "simixpch.h"
#include "IconLibrary.h"
#include "Simulatrix/ResourceManager/ResourceManager.h"

namespace Simulatrix {
    Ref<Texture2D> IconLibrary::LoadIconByName(std::string name) {
        auto fullPath = ResourceManager::GetIO()->GetCurrentDir().GetParentDir().Directory + "\\Simulatrix\\resources\\icons\\" + name + ".png";
        Ref<Texture2D> texture = Ref<Texture2D>(Texture2D::Create(Path(fullPath, PathType::File)));
        m_Icons.emplace(name, texture);
        return texture;
    }

    Ref<Texture2D> IconLibrary::GetIconByName(std::string name) {
        return m_Icons[name];
    }
}
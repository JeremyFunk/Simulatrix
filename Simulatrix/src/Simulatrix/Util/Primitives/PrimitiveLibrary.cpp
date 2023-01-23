#include "simixpch.h"
#include "Simulatrix/Core/Core.h"
#include "Simulatrix/ResourceManager/ResourceManager.h"
#include "simixpch.h"
#include "PrimitiveLibrary.h"
#include "Primitive.h"
#include <glm/glm.hpp>
#include "PrimitivePlane.h"
#include "PrimitiveCube.h"


namespace Simulatrix {
    std::vector<Ref<Primitive>> PrimitiveLibrary::s_Primitives;
    std::vector<Ref<SceneModel>> PrimitiveLibrary::s_LoadedModels;
    std::vector<std::string> PrimitiveLibrary::s_Names;

    std::vector<std::string> PrimitiveLibrary::GetNames() {
        return s_Names;
    }

    void PrimitiveLibrary::Initialize() {
        LoadPrimitive(CreateRef<PrimitivePlane>());
        LoadPrimitive(CreateRef<PrimitiveCube>());
    }
    
    void PrimitiveLibrary::LoadPrimitive(Ref<Primitive> primitive) {
        auto s = ResourceManager::SceneModelFromData(primitive->GetPrimitiveData(), primitive->GetName());
        s->ID = 1000 + s_LoadedModels.size();
        s->IsPrimitive = true;
        s_LoadedModels.push_back(s);
        s_Primitives.push_back(primitive);
        s_Names.push_back(primitive->GetName());
    }
    
    Ref<SceneModel> PrimitiveLibrary::GetModel(std::string name) {
        for (int i = 0; i < s_Primitives.size(); i++) {
            if (s_Primitives[i]->GetName() == name) {
                return s_LoadedModels[i];
            }
        }
    }
    Ref<SceneModel> PrimitiveLibrary::GetModel(UUID uuid) {
        for (auto& m : s_LoadedModels) {
            if (m->ID == uuid) {
                return m;
            }
        }
    }
}
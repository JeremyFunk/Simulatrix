#pragma once
#include "Primitive.h"

namespace Simulatrix {
    class PrimitiveLibrary {
    public:
        static void Initialize();
        
        static Ref<SceneModel> GetModel(std::string name);
        static Ref<SceneModel> GetModel(UUID uuid);
        static std::vector<std::string> GetNames();
        static std::vector<Ref<SceneModel>> GetModels() {
            return s_LoadedModels;
        }
    private:
        static void LoadPrimitive(Ref<Primitive> primitive);
        static std::vector<Ref<Primitive>> s_Primitives;
        static std::vector<Ref<SceneModel>> s_LoadedModels;
        static std::vector<std::string> s_Names;
    };
}
#pragma once
#include "Simulatrix/ResourceManager/ResourceData.h"
#include "Simulatrix/Scene/SceneData.h"

namespace Simulatrix {
    class MeshLoader {
    public:
        virtual SceneMesh Load(ResourceMesh& t) = 0;
    };
}
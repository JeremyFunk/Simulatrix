#pragma once
#include "Simulatrix/ResourceManager/Loader/MeshLoader.h"

namespace Simulatrix {
    class OpenGLMeshLoader : public MeshLoader {
    public:
        SceneMesh Load(ResourceMesh& t) override;
    };
}
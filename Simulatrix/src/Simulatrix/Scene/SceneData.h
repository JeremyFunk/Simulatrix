#pragma once
#include "Simulatrix/Renderer/VertexArray.h"
#include "Simulatrix/Renderer/Texture.h"
#include "Simulatrix/Core/UUID.h"

namespace Simulatrix {
    struct SceneMesh {
        Ref<VertexArray> VAO;
        unsigned int IndexCount;
        SceneMesh(Ref<VertexArray> VAO, unsigned int IndexCount) : VAO(VAO), IndexCount(IndexCount){}
    };

    enum class ColorFormat {
        R, RG, RGB, RGBA
    };

    struct SceneModel {
        UUID ID;
        std::vector<SceneMesh> Meshes;
        std::vector<UUID> Textures;
    };
}
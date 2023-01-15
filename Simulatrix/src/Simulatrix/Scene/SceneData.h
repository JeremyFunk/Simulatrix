#pragma once
#include "Simulatrix/Renderer/VertexArray.h"
#include "Simulatrix/Renderer/Texture.h"

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
        unsigned int ID;
        std::vector<SceneMesh> Meshes;
        std::vector<Ref<Texture2D>> Textures;
    };
}
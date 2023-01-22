#pragma once
#include "Simulatrix/Renderer/VertexArray.h"
#include "Simulatrix/Renderer/Texture.h"
#include "Simulatrix/Core/UUID.h"

namespace Simulatrix {
    struct SceneMesh {
        Ref<VertexArray> VAO;
        uint32_t IndexCount;
        SceneMesh(Ref<VertexArray> VAO, uint32_t IndexCount) : VAO(VAO), IndexCount(IndexCount){}
    };

    enum class ColorFormat {
        R, RG, RGB, RGBA
    };

    struct SceneModel {
        UUID ID;
        Path Path;
        std::vector<SceneMesh> Meshes;
        std::vector<Ref<Texture2D>> Textures;
    };
}
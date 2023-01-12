#pragma once
#include "Simulatrix/Renderer/VertexArray.h"
#include "Simulatrix/Renderer/Texture.h"

namespace Simulatrix {
    struct SceneMesh {
        std::shared_ptr<VertexArray> VAO;
        unsigned int IndexCount;
        SceneMesh(std::shared_ptr<VertexArray> VAO, unsigned int IndexCount) : VAO(VAO), IndexCount(IndexCount){}
        SceneMesh(VertexArray* vao, unsigned int IndexCount) : IndexCount(IndexCount) {
            VAO.reset(vao);
        }
    };

    enum class ColorFormat {
        R, RG, RGB, RGBA
    };

    struct SceneModel {
        unsigned int ID;
        std::vector<SceneMesh> Meshes;
        std::vector<std::shared_ptr<Texture2D>> Textures;
    };
}
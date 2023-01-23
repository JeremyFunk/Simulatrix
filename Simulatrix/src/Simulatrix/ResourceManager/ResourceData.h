#pragma once
#include <glm/glm.hpp>

namespace Simulatrix {

#define MAX_BONE_INFLUENCE 3
    struct ResourceVertex {
        // position
        glm::vec3 Position;
        // normal
        glm::vec3 Normal;
        // texCoords
        glm::vec2 TexCoords;
        // tangent
        glm::vec3 Tangent;
        // bitangent
        glm::vec3 Bitangent;
        ////bone indexes which will influence this vertex
        //int m_BoneIDs[MAX_BONE_INFLUENCE];
        ////weights from each bone
        //float m_Weights[MAX_BONE_INFLUENCE];

        ResourceVertex() {}
        ResourceVertex(glm::vec3 position, glm::vec3 normal, glm::vec2 texCoords, glm::vec3 tangent, glm::vec3 bitangent)
        {
            Position = position;
            Normal = normal;
            TexCoords = texCoords;
            Tangent = tangent;
            Bitangent = bitangent;
        }
    };

    struct ResourceTexture {
        std::string path;
    };

    class ResourceMesh {
    public:
        // mesh Data
        std::vector<ResourceVertex>       vertices;
        std::vector<uint32_t>         indices;
        std::vector<ResourceTexture>      textures;

        ResourceMesh() {
            
        }

        // constructor
        ResourceMesh(std::vector<ResourceVertex> vertices, std::vector<uint32_t> indices, std::vector<ResourceTexture> textures)
        {
            this->vertices = vertices;
            this->indices = indices;
            this->textures = textures;
        }
    };

    struct ResourceModel {
        std::vector<ResourceTexture> TexturesLoaded;
        std::vector<ResourceMesh> Meshes;
    };

}
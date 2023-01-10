#include "simixpch.h"
#include "OBJParser.h"
#include "Simulatrix/Core/Core.h"
namespace Simulatrix {
    void loadModel(Path const& path, ResourceModel& result);
    void processNode(aiNode* node, const aiScene* scene, ResourceModel& result);
    ResourceMesh processMesh(aiMesh* mesh, const aiScene* scene, ResourceModel& result);
    std::vector<ResourceTexture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName, ResourceModel& result);

    std::vector<std::string> OBJParser::GetAvailableFileEndings()
    {
        m_SupportedElements.push_back("obj");
        m_SupportedElements.push_back("mtl");
        return m_SupportedElements;
    }
    bool OBJParser::CanParseFile(Path path)
    {
        if (std::find(m_SupportedElements.begin(), m_SupportedElements.end(), path.FileEnding) != m_SupportedElements.end()) {
            return true;
        }
        return false;
    }


    ResourceModel OBJParser::Parse(Path path)
    {
        SIMIX_CORE_ASSERT(CanParseFile(path), "Cannot parse file!");

        ResourceModel result;
        loadModel(path, result);
        return result;
    }

    void loadModel(Path const& path, ResourceModel& result)
    {
        // read file via ASSIMP
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path.PathString, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
        // check for errors
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
        {
            SIMIX_CORE_ASSERT(false, "Assimp error: {0}", importer.GetErrorString())
                return;
        }

        // process ASSIMP's root node recursively
        processNode(scene->mRootNode, scene, result);
    }

    // processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
    void processNode(aiNode* node, const aiScene* scene, ResourceModel& result)
    {
        // process each mesh located at the current node
        for (unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            // the node object only contains indices to index the actual objects in the scene. 
            // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            result.Meshes.push_back(processMesh(mesh, scene, result));
        }
        // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
        for (unsigned int i = 0; i < node->mNumChildren; i++)
        {
            processNode(node->mChildren[i], scene, result);
        }

    }

    ResourceMesh processMesh(aiMesh* mesh, const aiScene* scene, ResourceModel& result)
    {
        // data to fill
        std::vector<ResourceVertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<ResourceTexture> textures;

        // walk through each of the mesh's vertices
        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            ResourceVertex vertex;
            glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
            // positions
            vector.x = mesh->mVertices[i].x;
            vector.y = mesh->mVertices[i].y;
            vector.z = mesh->mVertices[i].z;
            vertex.Position = vector;
            // normals
            if (mesh->HasNormals())
            {
                vector.x = mesh->mNormals[i].x;
                vector.y = mesh->mNormals[i].y;
                vector.z = mesh->mNormals[i].z;
                vertex.Normal = vector;
            }
            // texture coordinates
            if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
            {
                glm::vec2 vec;
                // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
                // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
                vec.x = mesh->mTextureCoords[0][i].x;
                vec.y = mesh->mTextureCoords[0][i].y;
                vertex.TexCoords = vec;
                // tangent
                vector.x = mesh->mTangents[i].x;
                vector.y = mesh->mTangents[i].y;
                vector.z = mesh->mTangents[i].z;
                vertex.Tangent = vector;
                // bitangent
                vector.x = mesh->mBitangents[i].x;
                vector.y = mesh->mBitangents[i].y;
                vector.z = mesh->mBitangents[i].z;
                vertex.Bitangent = vector;
            }
            else
                vertex.TexCoords = glm::vec2(0.0f, 0.0f);

            vertices.push_back(vertex);
        }
        // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            // retrieve all indices of the face and store them in the indices vector
            for (unsigned int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }
        // process materials
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
        // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
        // Same applies to other texture as the following list summarizes:
        // diffuse: texture_diffuseN
        // specular: texture_specularN
        // normal: texture_normalN

        // 1. diffuse maps
        std::vector<ResourceTexture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse", result);
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        // 2. specular maps
        std::vector<ResourceTexture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular", result);
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        // 3. normal maps
        std::vector<ResourceTexture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal", result);
        textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
        // 4. height maps
        std::vector<ResourceTexture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height", result);
        textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

        // return a mesh object created from the extracted mesh data
        return ResourceMesh(vertices, indices, textures);
    }

    // checks all material textures of a given type and loads the textures if they're not loaded yet.
    // the required info is returned as a Texture struct.
    std::vector<ResourceTexture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName, ResourceModel& result)
    {
        std::vector<ResourceTexture> textures;
        for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
        {
            aiString str;
            mat->GetTexture(type, i, &str);
            // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
            bool skip = false;
            for (unsigned int j = 0; j < result.TexturesLoaded.size(); j++)
            {
                if (std::strcmp(result.TexturesLoaded[j].path.data(), str.C_Str()) == 0)
                {
                    textures.push_back(result.TexturesLoaded[j]);
                    skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
                    break;
                }
            }
            if (!skip)
            {   // if texture hasn't been loaded already, load it
                ResourceTexture texture;
                texture.type = typeName;
                texture.path = str.C_Str();
                textures.push_back(texture);
                result.TexturesLoaded.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
            }
        }
        return textures;
    }
}
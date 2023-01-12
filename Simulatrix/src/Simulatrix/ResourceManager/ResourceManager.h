#pragma once
#include "Simulatrix/Core/IOWrapper.h"
#include "Simulatrix/ResourceManager/ResourceData.h"
#include "Simulatrix/Core/FileWatcher.h"
#include "Simulatrix/ResourceManager/Parser/TextureParser.h"
#include "Simulatrix/ResourceManager/Parser/ModelParser.h"
#include "Simulatrix/ResourceManager/Loader/MeshLoader.h"

namespace Simulatrix {
    class ResourceManager {
    public:
        ResourceManager();
        ~ResourceManager();
        static std::shared_ptr<IOWrapper> GetIO() { return s_Instance->m_Wrapper; }
        static ResourceManager* Get() { return s_Instance; }
        void Update();
        const SceneModel& GetModel(Path& path);
        const SceneModel& GetModel(uint32_t id);
        const std::shared_ptr<Texture2D> GetTexture(Path& path);
        const std::shared_ptr<Texture2D> GetTexture(uint32_t id);
    private:
        void Load(Path& path);
        void LoadModel(Path& path, ModelParser* parser);
        void LoadTexture(Path& path);
    private:
        static ResourceManager* s_Instance;
        std::shared_ptr<IOWrapper> m_Wrapper;
        std::shared_ptr <FileWatcher> m_ResourceWatcher;
        std::vector<ModelParser*> m_ModelParsers;
        std::vector<TextureParser*> m_TextureParsers;
        std::unordered_map<std::string, uint32_t> m_LoadedModelIDs;
        std::unordered_map<uint32_t, SceneModel> m_LoadedModels;

        std::unordered_map<std::string, uint32_t> m_LoadedTextureIDs;
        std::unordered_map<uint32_t, std::shared_ptr<Texture2D>> m_LoadedTextures;
        std::thread m_FileWatcherThread;

        MeshLoader* m_MeshLoader;
    };
}
#pragma once
#include "Simulatrix/Core/IOWrapper.h"
#include "Simulatrix/ResourceManager/ResourceData.h"
#include "Simulatrix/Core/FileWatcher.h"
#include "Simulatrix/ResourceManager/Parser/TextureParser.h"
#include "Simulatrix/ResourceManager/Parser/ModelParser.h"
#include "Simulatrix/ResourceManager/Loader/MeshLoader.h"
#include "Simulatrix/Core/UUID.h"
#include "Simulatrix/Core/Core.h"

namespace Simulatrix {
    class ResourceManager {
    public:
        ResourceManager();
        ~ResourceManager();
        static Ref<IOWrapper> GetIO() { return s_Instance->m_Wrapper; }
        static ResourceManager* Get() { return s_Instance; }
        void Update();
        const SceneModel& GetModel(Path& path);
        const UUID GetModelID(Path& path);
        const SceneModel& GetModel(UUID id);
        const Ref<Texture2D> GetTexture(Path& path);
        const Ref<Texture2D> GetOrLoadTexture(Path& path);
        const UUID GetTextureID(Path& path);
        const Ref<Texture2D> GetTexture(UUID id);
        const File GetFileStructure() {
            while (!m_ResourceWatcher->LockFileStructure()) {}
            auto f = m_ResourceWatcher->GetFileStructure().Clone();
            m_ResourceWatcher->UnlockFileStructure();
            f.SetParents();
            return f;
        }
    private:
        void Load(Path& path);
        void LoadModel(Path& path, ModelParser* parser);
        void LoadTexture(Path& path);
    private:
        static ResourceManager* s_Instance;
        Ref<IOWrapper> m_Wrapper;
        Ref <FileWatcher> m_ResourceWatcher;
        std::vector<ModelParser*> m_ModelParsers;
        std::vector<TextureParser*> m_TextureParsers;
        std::unordered_map<std::string, UUID> m_LoadedModelIDs;
        std::unordered_map<UUID, SceneModel> m_LoadedModels;

        std::unordered_map<std::string, UUID> m_LoadedTextureIDs;
        std::unordered_map<UUID, Ref<Texture2D>> m_LoadedTextures;
        std::thread m_FileWatcherThread;

        MeshLoader* m_MeshLoader;
    };
}
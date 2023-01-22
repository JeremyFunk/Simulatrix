#pragma once
#include "Simulatrix/Core/IOWrapper.h"
#include "Simulatrix/ResourceManager/ResourceData.h"
#include "Simulatrix/Core/FileWatcher.h"
#include "Simulatrix/ResourceManager/Parser/TextureParser.h"
#include "Simulatrix/ResourceManager/Parser/ModelParser.h"
#include "Simulatrix/ResourceManager/Loader/MeshLoader.h"
#include "Simulatrix/Renderer/Shader.h"
#include "Simulatrix/Core/UUID.h"
#include "Simulatrix/Core/Core.h"
#include "Simulatrix/Util/IdentifierMap.h"

namespace Simulatrix {
    class ResourceManager {
    public:
        ResourceManager();
        ~ResourceManager();
        static Ref<IOWrapper> GetIO() { return s_Instance->m_Wrapper; }
        static ResourceManager* Get() { return s_Instance; }
        void Update();

        const Ref<SceneModel> GetModel(Path& path);
        const Ref<SceneModel> GetOrLoadModel(Path& path, UUID uuid = UUID());
        const UUID GetModelID(Path& path);
        const Ref<SceneModel> GetModel(UUID& id);

        const Ref<Texture2D> GetTexture(Path& path);
        const Ref<Texture2D> GetOrLoadTexture(Path& path, UUID uuid = UUID());
        const UUID GetTextureID(Path& path);
        const Ref<Texture2D> GetTexture(UUID& id);

        const Ref<Shader> GetOrLoadShader(Path& path, UUID uuid = UUID());
        const Ref<Shader> GetShader(UUID& id);

        IdentifierMap<Ref<Texture2D>> GetLoadedTextures() {
            return m_LoadedTextures;
        }
        IdentifierMap<Ref<SceneModel>> GetLoadedModels() {
            return m_LoadedModels;
        }
        IdentifierMap<Ref<Shader>> GetLoadedShaders() {
            return m_LoadedShaders;
        }

        const File GetFileStructure() {
            while (!m_ResourceWatcher->LockFileStructure()) {}
            auto f = m_ResourceWatcher->GetFileStructure().Clone();
            m_ResourceWatcher->UnlockFileStructure();
            f.SetParents();
            return f;
        }
    private:
        void Load(Path& path, UUID uuid = UUID());
        void Reload(Path& path);
        void LoadModel(Path& path, ModelParser* parser, UUID uuid);
        void LoadTexture(Path& path, UUID uuid);
    private:
        static ResourceManager* s_Instance;
        Ref<IOWrapper> m_Wrapper;
        Ref <FileWatcher> m_ResourceWatcher;
        std::vector<ModelParser*> m_ModelParsers;
        std::vector<TextureParser*> m_TextureParsers;
        bool m_Initializing = true;

        IdentifierMap<Ref<SceneModel>> m_LoadedModels;
        IdentifierMap<Ref<Texture2D>> m_LoadedTextures;
        IdentifierMap<Ref<Shader>> m_LoadedShaders;
        std::vector<Path> m_LoadedFiles;

        std::thread m_FileWatcherThread;

        MeshLoader* m_MeshLoader;
    };
}
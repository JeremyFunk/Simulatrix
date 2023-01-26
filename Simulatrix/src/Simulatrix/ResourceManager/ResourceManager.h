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
#include "Simulatrix/Util/Primitives/PrimitiveLibrary.h"
namespace Simulatrix {
    class ResourceManager {
    public:
        static Ref<IOWrapper> GetIO() { return m_Wrapper; }
        static void Init();
        static void Update();
        static void CleanUp();

        static const Ref<SceneModel> GetModel(Path& path);
        static const Ref<SceneModel> GetOrLoadModel(Path& path, UUID uuid = UUID());
        static const UUID GetModelID(Path& path);
        static const Ref<SceneModel> GetModel(UUID& id);

        static const Ref<Texture2D> GetTexture(Path& path);
        static const Ref<Texture2D> GetOrLoadTexture(Path& path, UUID uuid = UUID());
        static const UUID GetTextureID(Path& path);
        static const Ref<Texture2D> GetTexture(UUID& id);

        static const Ref<Shader> GetOrLoadShader(Path& path, UUID uuid = UUID());
        static const Ref<Shader> GetShader(UUID& id);

        static IdentifierMap<Ref<Texture2D>> GetLoadedTextures() {
            return m_LoadedTextures;
        }
        static IdentifierMap<Ref<SceneModel>> GetLoadedModels() {
            return m_LoadedModels;
        }
        static IdentifierMap<Ref<Shader>> GetLoadedShaders() {
            return m_LoadedShaders;
        }

        static const File GetFileStructure() {
            while (!m_ResourceWatcher->LockFileStructure()) {}
            auto f = m_ResourceWatcher->GetFileStructure().Clone();
            m_ResourceWatcher->UnlockFileStructure();
            f.SetParents();
            return f;
        }

        static Ref<SceneModel> GetPrimitive(std::string name) {
            return PrimitiveLibrary::GetModel(name);
        }
        static Ref<SceneModel> GetPrimitive(UUID uuid) {
            return PrimitiveLibrary::GetModel(uuid);
        }
        static std::vector<Ref<SceneModel>> GetPrimitives() {
            return PrimitiveLibrary::GetModels();
        }
        static bool FileIsTexture(Path& path);
        

        static Ref<SceneModel> SceneModelFromData(ResourceModel& mesh, std::string name, UUID uuid = UUID());
    private:
        static void Load(Path& path, UUID uuid = UUID());
        static void Reload(Path& path);
        static void LoadModel(Path& path, ModelParser* parser, UUID uuid);
        static void LoadTexture(Path& path, UUID uuid);
    private:
        static Ref<IOWrapper> m_Wrapper;
        static Ref <FileWatcher> m_ResourceWatcher;
        static std::vector<ModelParser*> m_ModelParsers;
        static std::vector<TextureParser*> m_TextureParsers;
        static bool m_Initializing;

        static IdentifierMap<Ref<SceneModel>> m_LoadedModels;
        static IdentifierMap<Ref<Texture2D>> m_LoadedTextures;
        static IdentifierMap<Ref<Shader>> m_LoadedShaders;
        static std::vector<Path> m_LoadedFiles;

        static std::thread m_FileWatcherThread;

        static MeshLoader* m_MeshLoader;
    };
}
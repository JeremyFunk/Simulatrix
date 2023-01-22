#include <simixpch.h>
#include "Simulatrix/Debug/Log.h"
#include "ResourceManager.h"
#ifdef SIMIX_PLATFORM_WINDOWS
#include <Simulatrix/Platform/Windows/WindowsIOWrapper.h>
#endif 

#include "Simulatrix/ResourceManager/Parser/OBJParser.h"
#include "Simulatrix/ResourceManager/Parser/DefaultTextureParser.h"

#include "Simulatrix/Renderer/RendererAPI.h"
#include "Simulatrix/Renderer/Renderer.h"

#include "Simulatrix/Platform/OpenGL/Loader/OpenGLMeshLoader.h"

namespace Simulatrix {
    ResourceManager* ResourceManager::s_Instance = nullptr;
    void RunThread(Ref<FileWatcher> m_ResourceWatcher) {
        m_ResourceWatcher->Start();
    }

    ResourceManager::ResourceManager() {
#ifdef SIMIX_PLATFORM_WINDOWS
        m_Wrapper.reset(new WindowsIOWrapper());
#endif 
        SIMIX_CORE_ASSERT(!s_Instance, "Resource Manager already exists!");
        s_Instance = this;
        m_ModelParsers.push_back(new OBJParser());
        m_TextureParsers.push_back(new DefaultTextureParser());

        switch (Renderer::GetAPI()) {
        case RendererAPI::API::None: SIMIX_CORE_ASSERT(false, "RendererAPI::None is not supported!");
        case RendererAPI::API::OpenGL:
            m_MeshLoader = new OpenGLMeshLoader();
            //m_TextureLoader = new OpenGLTextureLoader();
            break;
        default:
            SIMIX_CORE_ASSERT(false, "Unknown renderer API!");
        }

        m_ResourceWatcher.reset(new FileWatcher(m_Wrapper->GetCurrentDir().PathString + "\\resources\\raw\\", std::chrono::milliseconds(250)));
        m_ResourceWatcher->RunIteration();
        Update();
        m_Initializing = false;
        m_FileWatcherThread = std::thread(RunThread, m_ResourceWatcher);
    }

    ResourceManager::~ResourceManager() {
        m_ResourceWatcher->Stop();
        m_FileWatcherThread.join();
        for (auto parser : m_ModelParsers) {
            delete parser;
        }
    }

    void ResourceManager::LoadModel(Path& p, ModelParser* parser, UUID uuid) {
        auto resource = parser->Parse(p);
        auto model = new SceneModel();
        model->Path = p;
        model->ID = uuid;
        auto pointer = Ref<SceneModel>();
        pointer.reset(model);
        for (auto& tex : resource.TexturesLoaded) {
            if(!m_LoadedTextures.contains(tex.path)) {
                LoadTexture(Path(tex.path, PathType::File), UUID());
            }

            pointer->Textures.push_back(m_LoadedTextures[tex.path]);
        }

        for (auto& mesh : resource.Meshes) {
            auto result = m_MeshLoader->Load(mesh);
            pointer->Meshes.push_back(result);
        }
        m_LoadedModels.emplace(p.PathString, pointer->ID, pointer);
    }

    void ResourceManager::LoadTexture(Path& p, UUID uuid) {
        auto texture = Texture2D::Create(p);
        auto pointer = Ref<Texture2D>();
        pointer.reset(texture);
        pointer->SetID(uuid);
        m_LoadedFiles.push_back(p);
        m_LoadedTextures.emplace(p.PathString, pointer->GetID(), pointer);
    }

    const Ref<SceneModel> ResourceManager::GetModel(Path& path) {
        return m_LoadedModels[path.PathString];
    }
    const Ref<SceneModel> ResourceManager::GetOrLoadModel(Path& path, UUID uuid) {
        if (!m_LoadedModels.contains(path.PathString)) {
            Load(path, uuid);
        }
        return m_LoadedModels[path.PathString];
    }

    const UUID ResourceManager::GetModelID(Path& path) {
        return m_LoadedModels.getUUID(path.PathString);
    }
    const Ref<SceneModel> ResourceManager::GetModel(UUID& id) {
        return m_LoadedModels[id];
    }
    const Ref<Texture2D> ResourceManager::GetTexture(Path& path) {
        return m_LoadedTextures[path.PathString];
    }
    const Ref<Texture2D> ResourceManager::GetOrLoadTexture(Path& path, UUID uuid) {
        if (!m_LoadedTextures.contains(path.PathString)) {
            LoadTexture(path, uuid);
        }

        return m_LoadedTextures[path.PathString];
    }
    const UUID ResourceManager::GetTextureID(Path& path) {
        return m_LoadedTextures.getUUID(path.PathString);
    }
    const Ref<Texture2D> ResourceManager::GetTexture(UUID& id) {
        return m_LoadedTextures[id];
    }
    const std::string TEXTURE_FILE_ENDINGS[] = {
        "jpg",
        "png",
        "bmp"
    };
    
    void ResourceManager::Load(Path& path, UUID uuid) {
        if(path.FileEnding == "glsl") {
            auto shader = Shader::Create(path);
            auto pointer = Ref<Shader>();
            pointer.reset(shader);
            pointer->SetID(uuid);
            m_LoadedFiles.push_back(path);
            m_LoadedShaders.emplace(path.PathString, pointer->GetID(), pointer);
            return;
        }

        for (auto parser : m_ModelParsers) {
            if (parser->CanParseFile(path)) {
                m_LoadedFiles.push_back(path);
                LoadModel(path, parser, uuid);
                return;
            }
        }

        for (auto file : TEXTURE_FILE_ENDINGS) {
            if (path.FileEnding == file) {
                LoadTexture(path, uuid);
                return;
            }
        }
    }

    void ResourceManager::Reload(Path& path) {
        if (path.FileEnding == "glsl") {
            auto shader = m_LoadedShaders[path.PathString];
            shader->Reload(path);
        }

        /*for (auto parser : m_ModelParsers) {
            if (parser->CanParseFile(path)) {
                if (m_LoadedModels.size() > 0) {
                    std::cout << "SS" << std::endl;
                }
                LoadModel(path, parser);
                return;
            }
        }*/

        /*for (auto file : TEXTURE_FILE_ENDINGS) {
            if (path.FileEnding == file) {
                LoadTexture(path);
                return;
            }
        }*/
    }


    const Ref<Shader> ResourceManager::GetOrLoadShader(Path& path, UUID uuid) {
        if (!m_LoadedShaders.contains(path.PathString)) {
            Load(path, uuid);
        }
        return m_LoadedShaders[path.PathString];
    }
    const Ref<Shader> ResourceManager::GetShader(UUID& id) {
        return m_LoadedShaders[id];
    }

    void ResourceManager::Update() {
        /*if (m_Initializing) {

        }*/
        auto loader = OBJParser();
        //auto result = loader.ParseFile(Path("C:\\Users\\Jerem\\Documents\\GitHub\\Simulatrix\\Sandbox\\resources\\raw\\assets\\Backpack\\backpack.obj", PathType::File));
        if (m_ResourceWatcher->Lock()) {
            for (auto& a : *m_ResourceWatcher) {
                switch (a.second) {
                    case FileStatus::Created:
                        SIMIX_CORE_INFO("File created: {0}", a.first.to_string());
                        //Load(a.first);
                        break;
                    case FileStatus::Modified:
                        SIMIX_CORE_INFO("File modified: {0}", a.first.to_string());
                        for (auto& p : m_LoadedFiles) {
                            if (p.PathString == a.first.PathString) {
                                Reload(a.first);
                            }
                        }
                        
                        break;
                    case FileStatus::Erased:
                        SIMIX_CORE_INFO("File erased: {0}", a.first.to_string());
                        //Delete(a.first);
                        break;
                    default:
                        std::cout << "Error! Unknown file status.\n";

                    }
            }
            m_ResourceWatcher->Clear();
            m_ResourceWatcher->Unlock();
        }
    }
}



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
    void RunThread(std::shared_ptr<FileWatcher> m_ResourceWatcher) {
        m_ResourceWatcher->Start();
    }

    ResourceManager::ResourceManager() {
#ifdef SIMIX_PLATFORM_WINDOWS
        m_Wrapper.reset(new WindowsIOWrapper());
#endif 
        m_ResourceWatcher.reset(new FileWatcher(m_Wrapper->GetCurrentDir().PathString + "\\resources\\raw\\", std::chrono::milliseconds(250)));
        m_FileWatcherThread = std::thread(RunThread, m_ResourceWatcher);
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
    }

    ResourceManager::~ResourceManager() {
        m_ResourceWatcher->Stop();
        m_FileWatcherThread.join();
        for (auto parser : m_ModelParsers) {
            delete parser;
        }
    }

    void ResourceManager::LoadModel(Path& p, ModelParser* parser) {
        auto resource = parser->Parse(p);
        SceneModel model;
        for (auto& tex : resource.TexturesLoaded) {
            if (m_LoadedTextureIDs.find(tex.path) == m_LoadedTextureIDs.end()) {
                auto texPath = Path(tex.path, PathType::File);
                LoadTexture(texPath);
            }

            model.Textures.push_back(m_LoadedTextures[m_LoadedTextureIDs[tex.path]]);
        }

        for (auto& mesh : resource.Meshes) {
            auto result = m_MeshLoader->Load(mesh);
            model.Meshes.push_back(result);
        }
        model.ID = m_LoadedModelIDs.size();

        m_LoadedModelIDs.emplace(p.FileName, model.ID);
        m_LoadedModels.emplace(model.ID, model);
    }

    void ResourceManager::LoadTexture(Path& p) {
        //auto resource = parser->Parse(p);
        auto texture = Texture2D::Create(p);
        auto pointer = std::shared_ptr<Texture2D>();
        pointer.reset(texture);
        //auto result = m_TextureLoader->Load(resource);

        uint32_t ID = m_LoadedTextureIDs.size();
        m_LoadedTextureIDs.emplace(p.FileName, ID);
        m_LoadedTextures.emplace(ID, pointer);
    }


    const SceneModel& ResourceManager::GetModel(Path& path) {
        return m_LoadedModels[m_LoadedModelIDs[path.PathString]];
    }
    const SceneModel& ResourceManager::GetModel(uint32_t id) {
        return m_LoadedModels[id];
    }
    const std::shared_ptr<Texture2D> ResourceManager::GetTexture(Path& path) {
        return m_LoadedTextures[m_LoadedTextureIDs[path.PathString]];
    }
    const std::shared_ptr<Texture2D> ResourceManager::GetTexture(uint32_t id) {
        return m_LoadedTextures[id];
    }
    const std::string TEXTURE_FILE_ENDINGS[] = {
        "jpg",
        "png",
        "bmp"
    };
    
    void ResourceManager::Load(Path& path) {
        for (auto parser : m_ModelParsers) {
            if (parser->CanParseFile(path)) {
                LoadModel(path, parser);
                return;
            }
        }

        /*for (auto file : TEXTURE_FILE_ENDINGS) {
            if (path.FileEnding == file) {
                LoadTexture(path);
                return;
            }
        }*/
    }

    void ResourceManager::Update() {
        auto loader = OBJParser();
        //auto result = loader.ParseFile(Path("C:\\Users\\Jerem\\Documents\\GitHub\\Simulatrix\\Sandbox\\resources\\raw\\assets\\Backpack\\backpack.obj", PathType::File));
        if (m_ResourceWatcher->Lock()) {
            for (auto& a : *m_ResourceWatcher) {
                switch (a.second) {
                    case FileStatus::Created:
                        SIMIX_CORE_INFO("File created: {0}", a.first.to_string());
                        Load(a.first);
                        break;
                    case FileStatus::Modified:
                        SIMIX_CORE_INFO("File modified: {0}", a.first.to_string());
                        //Reload(a.first);
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


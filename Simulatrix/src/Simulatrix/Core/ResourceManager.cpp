#include <simixpch.h>
#include "Simulatrix/Debug/Log.h"
#include "ResourceManager.h"
#ifdef SIMIX_PLATFORM_WINDOWS
#include <Simulatrix/Platform/Windows/WindowsIOWrapper.h>
#endif 
#include "Simulatrix/Scene/OBJParser.h"
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
    }

    ResourceManager::~ResourceManager() {
        m_ResourceWatcher->Stop();
        m_FileWatcherThread.join();
        for (auto parser : m_ModelParsers) {
            delete parser;
        }
    }

    ResourceModel ResourceManager::LoadModel(Path& p) {
        for (auto parser : m_ModelParsers) {
            if (parser->CanParseFile(p)) {
                return parser->Parse(p);
            }
        }
        return ResourceModel();
    }

    void ResourceManager::Update() {
        auto loader = OBJParser();
        //auto result = loader.ParseFile(Path("C:\\Users\\Jerem\\Documents\\GitHub\\Simulatrix\\Sandbox\\resources\\raw\\assets\\Backpack\\backpack.obj", PathType::File));
        if (m_ResourceWatcher->Lock()) {
            for (auto& a : *m_ResourceWatcher) {
                switch (a.second) {
                    case FileStatus::Created:
                        SIMIX_CORE_INFO("File created: {0}", a.first.to_string());
                        break;
                    case FileStatus::Modified:
                        SIMIX_CORE_INFO("File modified: {0}", a.first.to_string());
                            break;
                    case FileStatus::Erased:
                        SIMIX_CORE_INFO("File erased: {0}", a.first.to_string());
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



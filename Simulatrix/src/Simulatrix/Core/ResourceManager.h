#pragma once
#include "Simulatrix/Core/IOWrapper.h"
#include "FileWatcher.h"
#include "Simulatrix/Scene/ModelParser.h"
#include "Simulatrix/Scene/SceneData.h"
namespace Simulatrix {



    class ResourceManager {
    public:
        ResourceManager();
        ~ResourceManager();
        static std::shared_ptr<IOWrapper> GetIO() { return s_Instance->m_Wrapper; }
        static ResourceManager* Get() { return s_Instance; }
        ResourceModel LoadModel(Path& path);
        void Update();
    private:
        static ResourceManager* s_Instance;
        std::shared_ptr<IOWrapper> m_Wrapper;
        std::shared_ptr <FileWatcher> m_ResourceWatcher;
        std::vector<ModelParser*> m_ModelParsers;
        std::thread m_FileWatcherThread;
    };
}
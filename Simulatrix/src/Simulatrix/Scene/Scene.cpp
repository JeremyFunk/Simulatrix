#include "simixpch.h"
#include "Scene.h"
namespace Simulatrix {
    Scene::Scene() {
        m_Registry = entt::registry();
    }
    Scene::~Scene() {

    }

    void Scene::FileDropped(Path& path) {
        if (path.FileEnding == "obj") {
            auto id = ResourceManager::GetOrLoadModel(path);

            auto e2 = CreateEntity();
            e2.AddComponent<ComponentID>();
            e2.AddComponent<ComponentModel>(id);
            e2.AddComponent<ComponentTag>("Backpack");
            e2.AddComponent<ComponentTransform>();
        }
    }
}
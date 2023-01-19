#include "simixpch.h"
#include "Scene.h"
#include "Simulatrix/ResourceManager/ResourceManager.h"
namespace Simulatrix {
    Scene::Scene() {
        m_Registry = entt::registry();
    }
    Scene::~Scene() {

    }

    void Scene::FileDropped(Path& path) {
        if (path.FileEnding == "obj") {
            auto id = ResourceManager::Get()->GetOrLoadModel(path);

            auto e2 = CreateEntity();
            e2.AddComponent<ComponentModel>(id);
            e2.AddComponent<ComponentTag>("Backpack");
            e2.AddComponent<ComponentTransform>();
            e2.AddComponent<ComponentShader>(m_DefaultShaderID);
            //e2.AddComponent<ComponentTextureMaterial>();
        }
    }
}
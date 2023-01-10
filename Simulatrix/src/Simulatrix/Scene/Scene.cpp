#include "simixpch.h"
#include "Scene.h"

namespace Simulatrix {
    Scene::Scene() {
        m_Registry = entt::registry();
    }
    Scene::~Scene() {

    }
}
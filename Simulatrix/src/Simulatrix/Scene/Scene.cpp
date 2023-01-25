#include "simixpch.h"
#include "Scene.h"
#include "Simulatrix/Scene/SceneSerializer.h"
namespace Simulatrix {
    Scene::Scene() {
        m_Registry = entt::registry();
        m_PhysicsCommon = Ref<rp3d::PhysicsCommon>(new rp3d::PhysicsCommon());
        m_PhysicsWorld = m_PhysicsCommon->createPhysicsWorld();
    }
    Scene::~Scene() {

    }
}
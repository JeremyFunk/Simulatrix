#pragma once
#include "Action.h"
#include <glm/glm.hpp>
#include "Simulatrix/Core/Core.h"
#include "Simulatrix/Scene/Scene.h"

namespace Simulatrix {
    class Entity;

    class ActionTransform : public Action
    {
    public:
        ActionTransform(Entity entity);
        ~ActionTransform();

        void Cancel() override;
        glm::vec3 GetLocation() { return m_Location; }
        glm::vec3 GetRotation() { return m_Rotation; }
        glm::vec3 GetScale() { return m_Scale; }
    private:
        glm::vec3 m_Location, m_Scale, m_Rotation;
        Entity m_Entity;
    };
}
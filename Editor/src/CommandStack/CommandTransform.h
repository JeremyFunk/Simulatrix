#pragma once
#include "Command.h"
#include <glm/glm.hpp>
#include "Simulatrix/Core/Core.h"
#include "Simulatrix/Scene/Scene.h"
namespace Simulatrix {
    class CommandTransform : public Command {
     public:
        CommandTransform(Entity entity, glm::vec3 oldPos, glm::vec3 newPos, glm::vec3 oldRot, glm::vec3 newRot, glm::vec3 oldScale, glm::vec3 newScale);
        void Undo() override;
        void Redo() override;
        std::string GetName() override {
            return "Transform";
        }
            
    private:
        Entity m_Entity;
        glm::vec3 m_OldPos, m_NewPos;
        glm::vec3 m_OldRot, m_NewRot;
        glm::vec3 m_OldScale, m_NewScale;
    };
}
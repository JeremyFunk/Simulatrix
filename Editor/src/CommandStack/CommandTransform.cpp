#pragma once
#include <simixpch.h>
#include "CommandTransform.h"

namespace Simulatrix {
    CommandTransform::CommandTransform(Entity entity, glm::vec3 oldPos, glm::vec3 newPos, glm::vec3 oldRot, glm::vec3 newRot, glm::vec3 oldScale, glm::vec3 newScale)
        : m_Entity(entity), m_OldPos(oldPos), m_NewPos(newPos), m_OldRot(oldRot), m_NewRot(newRot), m_OldScale(oldScale), m_NewScale(newScale){}
    void CommandTransform::Undo() {
        auto& transform = m_Entity.GetComponent<ComponentTransform>();
        transform.Translation = m_OldPos;
        transform.Rotation = m_OldRot;
        transform.Scale = m_OldScale;
    }
    void CommandTransform::Redo() {
        auto& transform = m_Entity.GetComponent<ComponentTransform>();
        transform.Translation = m_NewPos;
        transform.Rotation = m_NewRot;
        transform.Scale = m_NewScale;
    }
}
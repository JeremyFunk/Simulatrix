
#include <simixpch.h>
#include "ActionTransform.h"

namespace Simulatrix {
    ActionTransform::ActionTransform(Entity entity) {
        m_Entity = entity;
        auto transform = m_Entity.GetComponent<ComponentTransform>();
        m_Location = transform.Translation;
        m_Rotation = transform.Rotation;
        m_Scale = transform.Scale;
    }
    
    ActionTransform::~ActionTransform()
    {
        
    }

    void ActionTransform::Cancel() {
        auto& transform = m_Entity.GetComponent<ComponentTransform>();
        transform.Translation = m_Location;
        transform.Rotation = m_Rotation;
        transform.Scale = m_Scale;
    }
}
#pragma once

#include "Simulatrix/Core/Core.h"
#include "Simulatrix/Events/Event.h"
#include <Simulatrix/Core/Timestep.h>
namespace Simulatrix {
    class Layer
    {
    public:
        Layer(const std::string& name = "Layer");

        virtual ~Layer();

        virtual void OnAttach(){}
        virtual void OnDetach() {}
        virtual void OnUpdate(Timestep ts) {}
        virtual void OnEvent(Event& e) {}

        inline const std::string& GetName() const { return m_DebugName; }
    protected:
        std::string m_DebugName;
    };
}


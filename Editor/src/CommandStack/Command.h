#pragma once
#include "Simulatrix/Core/Core.h"

namespace Simulatrix {
    class Command {
    public:
        virtual void Undo() = 0;
        virtual void Redo() = 0;
        virtual std::string GetName() = 0;
        
    };
}
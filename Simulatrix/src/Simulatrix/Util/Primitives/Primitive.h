#pragma once
#include "Simulatrix/ResourceManager/ResourceData.h"

namespace Simulatrix{
    class Primitive {
    public:
        virtual ~Primitive() {}
        virtual std::string GetName() = 0;
        virtual ResourceModel GetPrimitiveData() = 0;
    };
}
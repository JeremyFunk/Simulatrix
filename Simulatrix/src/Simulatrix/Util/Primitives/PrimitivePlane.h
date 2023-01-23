#pragma once
#include "Primitive.h"

namespace Simulatrix {
    class PrimitivePlane : public Primitive {
    public:
        PrimitivePlane() {
            
        }
        virtual std::string GetName() override {
            return "Plane";
        }
        virtual ResourceModel GetPrimitiveData() override;
    };  
}
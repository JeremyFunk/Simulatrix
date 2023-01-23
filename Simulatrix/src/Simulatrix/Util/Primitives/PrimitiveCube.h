#pragma once
#include "Primitive.h"

namespace Simulatrix {
    class PrimitiveCube : public Primitive {
    public:
        PrimitiveCube() {

        }
        virtual std::string GetName() override {
            return "Cube";
        }
        virtual ResourceModel GetPrimitiveData() override;
    };
}
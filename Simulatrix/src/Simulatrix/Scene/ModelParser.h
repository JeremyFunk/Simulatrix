#pragma once
#include "Simulatrix/Core/IOWrapper.h"
#include "Simulatrix/Scene/SceneData.h"
namespace Simulatrix {
    class ModelParser {
    public:
        virtual std::vector<std::string> GetAvailableFileEndings() = 0;
        virtual bool CanParseFile(Path path) = 0;
        virtual ResourceModel Parse(Path path) = 0;
    };
}
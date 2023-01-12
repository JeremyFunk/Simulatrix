#pragma once

#include "Simulatrix/Core/IOWrapper.h"
#include "Simulatrix/ResourceManager/ResourceData.h"

namespace Simulatrix {
    class TextureParser {
    public:
        virtual std::vector<std::string> GetAvailableFileEndings() = 0;
        virtual bool CanParseFile(Path path) = 0;
        virtual ResourceTexture Parse(Path path) = 0;
    };
}
#pragma once
#include "ModelParser.h"
#include "Simulatrix/Core/IOWrapper.h"
#include "Simulatrix/Core/Core.h"
namespace Simulatrix {

    class OBJParser : public ModelParser {
    public:
        OBJParser();
        virtual std::vector<std::string> GetAvailableFileEndings() override;
        virtual bool CanParseFile(Path path) override;
        virtual ResourceModel Parse(Path path) override;
    private:
        std::vector<std::string> m_SupportedElements;
    };
}
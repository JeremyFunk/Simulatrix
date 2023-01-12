#pragma once
#include "TextureParser.h"

namespace Simulatrix {

    class DefaultTextureParser : public TextureParser {
    public:
        DefaultTextureParser();
        virtual std::vector<std::string> GetAvailableFileEndings() override;
        virtual bool CanParseFile(Path path) override;
        virtual ResourceTexture Parse(Path path) override;
    private:
        std::vector<std::string> m_SupportedElements;
    };
}
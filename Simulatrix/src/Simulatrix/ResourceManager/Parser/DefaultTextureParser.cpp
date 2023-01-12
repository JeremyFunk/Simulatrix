#include <simixpch.h>
#include "DefaultTextureParser.h"
namespace Simulatrix {
    DefaultTextureParser::DefaultTextureParser() {
        m_SupportedElements.push_back("png");
        m_SupportedElements.push_back("jpg");
        m_SupportedElements.push_back("bmp");
    }

    std::vector<std::string> DefaultTextureParser::GetAvailableFileEndings()
    {
        return m_SupportedElements;
    }

    bool DefaultTextureParser::CanParseFile(Path path)
    {
        return false;
    }

    ResourceTexture DefaultTextureParser::Parse(Path path)
    {
        return ResourceTexture();
    }
}

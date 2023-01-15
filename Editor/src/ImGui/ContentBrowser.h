#pragma once
#include "IconLibrary.h"
namespace Simulatrix {
    class ContentBrowser {
    public:
        ContentBrowser(Ref<IconLibrary> iconLibrary) : m_IconLibrary(iconLibrary) {}
        void Render();
    private:
        Ref<IconLibrary> m_IconLibrary;
    };
}
#pragma once
#include "Core.h"
namespace Simulatrix {
    class SIMMAT_API Application
    {
    public:
        Application();
        virtual ~Application();
        void Run();
    };
    // To be defined in client.
    Application* CreateApplication();
}


#pragma once

#ifdef SIMMAT_PLATFORM_WINDOWS

extern Simulatrix::Application* Simulatrix::CreateApplication();

int main(int argc, char** argv) {
    auto app = Simulatrix::CreateApplication();
    app->Run();
    delete app;
}
#endif
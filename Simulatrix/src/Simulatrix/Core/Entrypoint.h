#pragma once

#ifdef SIMIX_PLATFORM_WINDOWS

extern Simulatrix::Application* Simulatrix::CreateApplication();

int main(int argc, char** argv) {
    Simulatrix::Log::Init();
    SIMIX_CORE_WARN("Initialized Log!");
    SIMIX_INFO("Initialized Log!");
    auto app = Simulatrix::CreateApplication();
    app->Run();
    delete app;
}
#endif
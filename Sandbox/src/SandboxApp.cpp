#include <Simulatrix.h>

class Sandbox : public Simulatrix::Application
{
public:
    Sandbox() {

    }

    ~Sandbox() {

    }
};

Simulatrix::Application* Simulatrix::CreateApplication() {
    return new Sandbox();
}
#pragma once
#include "Simulatrix/Core/Core.h"
#include "Simulatrix/Events/Event.h"
namespace Simulatrix {
    struct WindowProps {
        std::string Title;
        unsigned int Width, Height;

        WindowProps(const std::string& title = "Simulatrix", unsigned int width = 1280, unsigned int height = 720)
            : Width(width), Height(height), Title(title)
        {}
    };

    class SIMIX_API Window {
    public:
        using EventCallbackFn = std::function<void(Event&)>;

        virtual ~Window() {}
        virtual void OnUpdate() = 0;
        virtual unsigned int GetWidth() const = 0;
        virtual unsigned int GetHeight() const = 0;

        virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
        virtual void SetVSync(bool enabled) = 0;
        virtual bool IsVSync() const = 0;
        virtual void* GetNativeWindow() const = 0;

        static Scope<Window> Create(const WindowProps& props = WindowProps());
    };
}
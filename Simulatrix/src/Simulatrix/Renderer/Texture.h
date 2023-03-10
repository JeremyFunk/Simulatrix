#pragma once
#include "Simulatrix/Core/IOWrapper.h"
#include "Simulatrix/Core/Core.h"

namespace Simulatrix {
    class Texture {
    public:
        virtual ~Texture() = default;

        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;
        virtual uint32_t GetRendererID() const = 0;

        virtual const Path& GetPath() const = 0;

        virtual void SetData(void* data, uint32_t size) = 0;

        virtual void Bind(uint32_t slot = 0) const = 0;

        virtual bool IsLoaded() const = 0;

        virtual UUID GetID() const = 0;
        virtual void SetID(UUID& id) = 0;
    };

    class Texture2D : public Texture
    {
    public:
        static Texture2D* Create(uint32_t width, uint32_t height);
        static Texture2D* Create(const Path& path);
    };
}
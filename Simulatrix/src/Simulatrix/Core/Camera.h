#pragma once
#include <glm/glm.hpp>
#include <Simulatrix/Core/Timestep.h>
namespace Simulatrix {
    class Camera {
    public:
        virtual const glm::vec3& GetPosition() const = 0;
        virtual const glm::mat4x4& GetViewMatrix() const = 0;
        virtual void Update(Timestep delta) = 0;
    };
}
#pragma once
#include <glm/glm.hpp>
#include <Simulatrix/Core/Timestep.h>
namespace Simulatrix {
    class Camera {
    public:
        virtual glm::vec3 GetPosition() const = 0;
        virtual void SetPosition(glm::vec3 position) = 0;
        virtual glm::mat4x4 GetViewMatrix() const = 0;
        virtual void Update(Timestep delta) = 0;
    };
}
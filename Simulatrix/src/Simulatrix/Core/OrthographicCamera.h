#pragma once
#include "Camera.h"
namespace Simulatrix {
    class OrthographicCamera : public Camera {
    public:
        virtual const glm::vec3& GetPosition() const override;
        virtual const glm::mat4x4& GetViewMatrix() const override;
        virtual void Update(Timestep delta) override;
    private:
        glm::vec3 m_Position;
    };
}
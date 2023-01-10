#pragma once
#include "Camera.h"
namespace Simulatrix {
    class OrthographicCamera : public Camera {
    public:
        virtual glm::vec3 GetPosition() const override;
        virtual glm::mat4x4 GetViewMatrix() const override;
        virtual void SetPosition(glm::vec3 position) override;
        virtual void Update(Timestep delta) override;
    private:
        glm::vec3 m_Position;
    };
}
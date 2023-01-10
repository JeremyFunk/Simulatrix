#pragma once
#include "Camera.h"

namespace Simulatrix {
    const float YAW = -90.0f;
    const float PITCH = 0.0f;
    const float SPEED = 2.5f;
    const float SENSITIVITY = 0.1f;
    class ProjectionCamera : public Camera {
    public:
        ProjectionCamera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : m_Front(glm::vec3(0.0f, 0.0f, -1.0f))
        {
            m_Position = position;
            m_WorldUp = up;
            m_Yaw = yaw;
            m_Pitch = pitch;
            m_Velocity = SPEED;
            UpdateVectors();
        }
        virtual glm::vec3 GetPosition() const override;
        virtual glm::mat4x4 GetViewMatrix() const override;
        virtual void SetPosition(glm::vec3 position) override;
        virtual void Update(Timestep delta) override;
    private:
        virtual void UpdateVectors();
    private:
        glm::vec3 m_Position;
        glm::vec3 m_Front;
        glm::vec3 m_Up;
        glm::vec3 m_Right;
        glm::vec3 m_WorldUp;
        float m_Yaw;
        float m_Velocity;
        float m_Pitch;
    };
}
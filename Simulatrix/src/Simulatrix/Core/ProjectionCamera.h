#pragma once
#include "Camera.h"

namespace Simulatrix {
    const float YAW = -90.0f;
    const float PITCH = 0.0f;
    const float SPEED = 6.f;
    const float SENSITIVITY = 0.1f;
    class ProjectionCamera : public Camera {
    public:
        ProjectionCamera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH, float nearPlane = 0.1f, float farPlane = 100, float fov = 45.0) : m_Front(glm::vec3(0.0f, 0.0f, -1.0f)), m_NearPlane(nearPlane), m_FarPlane(farPlane), m_FOV(fov)
        {
            m_Position = position;
            m_WorldUp = up;
            m_Yaw = yaw;
            m_Pitch = pitch;
            m_Velocity = SPEED;
            UpdateVectors();
        }

        virtual inline float GetNearPlane() const override {
            return m_NearPlane;
        }
        virtual inline float GetFarPlane() const override {
            return m_FarPlane;
        }
        virtual inline float GetFOV() const override {
            return m_FOV;
        }

        virtual void SetNearPlane(float nearPlane) {
            m_NearPlane = nearPlane;
        }
        virtual void SetFarPlane(float farPlane){
            m_FarPlane = farPlane;
        }
        virtual void SetFOV(float fov){
            m_FOV = fov;
        }
        virtual glm::vec3 GetPosition() const override;
        virtual glm::mat4x4 GetViewMatrix() const override;
        virtual void SetPosition(glm::vec3 position) override;
        virtual void Update(Timestep delta) override;
        void SetFreecam(bool freecam);
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
        bool m_Freecam = false;
        float m_FOV, m_FarPlane, m_NearPlane;
    };
}
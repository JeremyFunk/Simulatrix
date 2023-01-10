#pragma once
#include "simixpch.h"
#include "ProjectionCamera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Simulatrix/Core/Input.h"
#include "Simulatrix/Debug/Log.h"

namespace Simulatrix {
    void ProjectionCamera::Update(Timestep delta) {
        if (Input::IsKeyPressed(Key::W)) {
            auto front = m_Front;
            front.y = 0;
            m_Position += glm::normalize(front) * m_Velocity * delta.GetSeconds();
        }
        if (Input::IsKeyPressed(Key::S)) {
            auto front = m_Front;
            front.y = 0;
            m_Position -= glm::normalize(front) * m_Velocity * delta.GetSeconds();
        }
        if (Input::IsKeyPressed(Key::A)) {
            m_Position -= m_Right * m_Velocity * m_Velocity * delta.GetSeconds();
        }
        if (Input::IsKeyPressed(Key::D)) {
            m_Position += m_Right * m_Velocity * m_Velocity * delta.GetSeconds();
        }
        if (Input::IsKeyPressed(Key::LeftShift)) {
            m_Position.y -= m_Velocity * m_Velocity * delta.GetSeconds();
        }
        if (Input::IsKeyPressed(Key::Space)) {
            m_Position.y += m_Velocity * m_Velocity * delta.GetSeconds();
        }
        float xoffset = Input::GetMouseDX() * SENSITIVITY;
        float yoffset = Input::GetMouseDY() * SENSITIVITY;

        m_Yaw += xoffset;
        m_Pitch += yoffset;

        if (m_Pitch > 89.0f)
            m_Pitch = 89.0f;
        if (m_Pitch < -89.0f)
            m_Pitch = -89.0f;

        UpdateVectors();
    }
    
    void ProjectionCamera::UpdateVectors() {
        glm::vec3 front;
        front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
        front.y = -sin(glm::radians(m_Pitch));
        front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
        m_Front = glm::normalize(front);
        m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
        m_Up = glm::normalize(glm::cross(m_Right, m_Front));
    }

    glm::vec3 ProjectionCamera::GetPosition() const
    {
        return m_Position;
    }

    glm::mat4 ProjectionCamera::GetViewMatrix() const
    {
        return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
    }
    void ProjectionCamera::SetPosition(glm::vec3 position)
    {
        m_Position = position;
    }
}
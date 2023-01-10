#include "simixpch.h"
#include "OrthographicCamera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Simulatrix {
    glm::vec3 OrthographicCamera::GetPosition() const
    {
        return m_Position;
    }
    glm::mat4x4 OrthographicCamera::GetViewMatrix() const
    {
        glm::mat4 m = glm::mat4(1.0);
        m = glm::translate(m, m_Position);
        return m;
    }

    void OrthographicCamera::SetPosition(glm::vec3 position) {
        m_Position = position;
    }
    void OrthographicCamera::Update(Timestep delta)
    {
    }
}
#include "simixpch.h"
#include "OrthographicCamera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Simulatrix {
    const glm::vec3& OrthographicCamera::GetPosition() const
    {
        return m_Position;
    }
    const glm::mat4x4& OrthographicCamera::GetViewMatrix() const
    {
        auto m = glm::mat4x4();
        m = glm::translate(m, m_Position);
        return m;
    }
    void OrthographicCamera::Update(Timestep delta)
    {
        m_Position.x += delta * .1f;
    }
}
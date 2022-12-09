#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Engine
{
    OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
        : m_ProjectionMatrix(glm::mat4(1.0f)),
        m_Position(glm::vec3(0.0f, 0.0f, 0.0f))
    {
        UpdateViewMatrix();
        ENG_TRACE("Created Orthographic Camera");
    }

    OrthographicCamera::~OrthographicCamera()
    {
        ENG_TRACE("Destroyed Orthographic Camera");
    }

    void OrthographicCamera::SetPosition(const glm::vec3 &position)
    {
        m_Position = position;
        UpdateViewMatrix();
    }

    void OrthographicCamera::UpdateViewMatrix()
    {
        m_ViewMatrix = glm::inverse(glm::translate(glm::mat4(1.0f), m_Position));
    }

    // TODO: implement after implementing an event system
    void OrthographicCamera::OnUpdate()
    {
    }

    void OrthographicCamera::OnEvent(Event &event)
    {
    }
}
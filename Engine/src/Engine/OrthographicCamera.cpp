#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Engine
{
    OrthographicCamera::OrthographicCamera(unsigned int width, unsigned int height)
        : m_Position(glm::vec3(0.0f, 0.0f, 1.0f)), m_Width(width), m_Height(height),
        m_ProjectionMatrix(glm::mat4(1.0f))
    {
        UpdateViewMatrix();
        ENG_TRACE("Created orthographic camera");
    }

    OrthographicCamera::~OrthographicCamera()
    {
        ENG_TRACE("Destroyed orthographic camera");
    }

    void OrthographicCamera::SetPosition(const glm::vec3 &position)
    {
        m_Position = position;
        UpdateViewMatrix();
    }

    void OrthographicCamera::UpdateViewMatrix()
    {
        m_ViewMatrix = glm::translate(glm::mat4(1.0f), -m_Position);
    }
}
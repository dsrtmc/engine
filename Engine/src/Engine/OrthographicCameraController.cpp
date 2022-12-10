#include "OrthographicCameraController.h"

#include "Input.h"
#include "KeyCodes.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Engine
{
    // Width and height used for creating a camera and setting its aspect ratio
    OrthographicCameraController::OrthographicCameraController(float width, float height)
        : m_Camera(0, width, 0, height), m_Position(glm::vec3(0.0f, 0.0f, 0.0f))
    {
        ENG_TRACE("Created Orthographic Camera Controller");
    }

    OrthographicCameraController::~OrthographicCameraController()
    {
        ENG_TRACE("Destroyed Orthographic Camera Controller");
    }

    void OrthographicCameraController::SetPosition(const glm::vec3 &position)
    {
        m_Position = position;
        m_Camera.SetPosition(m_Position);
    }

    void OrthographicCameraController::OnUpdate()
    {
        if (Input::IsKeyPressed(ENG_KEY_W))
            SetPosition(m_Position + glm::vec3(0.0f, 0.025f, 0.0f));
        if (Input::IsKeyPressed(ENG_KEY_S))
            SetPosition(m_Position + glm::vec3(0.0f, -0.025f, 0.0f));
        if (Input::IsKeyPressed(ENG_KEY_A))
            SetPosition(m_Position + glm::vec3(-0.025f, 0.0f, 0.0f));
        if (Input::IsKeyPressed(ENG_KEY_D))
            SetPosition(m_Position + glm::vec3(0.025f, 0.0f, 0.0f));
    }

    void OrthographicCameraController::OnEvent(Event &event)
    {
        if (Input::IsKeyPressed(ENG_KEY_R))
            SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    }
}
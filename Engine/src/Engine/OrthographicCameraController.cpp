#include "OrthographicCameraController.h"

#include "Input.h"
#include "KeyCodes.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Engine
{
    // Width and height used for creating a camera and setting its aspect ratio
    OrthographicCameraController::OrthographicCameraController(float width, float height)
        : m_Camera(0, width, 0, height), m_CameraPosition(glm::vec3(0.0f, 0.0f, 0.0f))
    {
        ENG_TRACE("Created Orthographic Camera Controller");
    }

    OrthographicCameraController::~OrthographicCameraController()
    {
        ENG_TRACE("Destroyed Orthographic Camera Controller");
    }

    void OrthographicCameraController::SetCameraPosition(const glm::vec3 &position)
    {
        m_CameraPosition = position;
        m_Camera.SetPosition(m_CameraPosition);
    }

    void OrthographicCameraController::SetCameraRotation(float rotation)
    {
        m_CameraRotation = rotation;
        m_Camera.SetRotation(m_CameraRotation);
    }

    void OrthographicCameraController::OnUpdate(float timestep)
    {
        // Multiply by 1000 to compensate for really low timestep values
        m_MovementSpeed = 50.0f * 1000.0f;
        if (Input::IsKeyPressed(ENG_KEY_W))
            m_CameraPosition.y += 0.01f * m_MovementSpeed * timestep;
        if (Input::IsKeyPressed(ENG_KEY_S))
            m_CameraPosition.y -= 0.01f * m_MovementSpeed * timestep;
        if (Input::IsKeyPressed(ENG_KEY_A))
            m_CameraPosition.x -= 0.01f * m_MovementSpeed * timestep;
        if (Input::IsKeyPressed(ENG_KEY_D))
            m_CameraPosition.x += 0.01f * m_MovementSpeed * timestep;
        if (Input::IsKeyPressed(ENG_KEY_Q))
            m_CameraRotation += 1.0f;
        if (Input::IsKeyPressed(ENG_KEY_E))
            m_CameraRotation -= 1.0f;

        SetCameraPosition(m_CameraPosition);
        SetCameraRotation(m_CameraRotation);
    }

    void OrthographicCameraController::OnEvent(Event &event)
    {
        if (Input::IsKeyPressed(ENG_KEY_R))
        {
            SetCameraPosition(glm::vec3(0.0f, 0.0f, 0.0f));
            SetCameraRotation(0.0f);
        }
    }
}
#pragma once

#include "OrthographicCamera.h"
#include "Event.h"
#include "MouseEvent.h"

#include <glm/glm.hpp>

namespace Engine
{
    class OrthographicCameraController
    {
    public:
        OrthographicCameraController(float aspectRatio);
        ~OrthographicCameraController();

        const std::shared_ptr<OrthographicCamera> GetCamera() const { return m_Camera; }
        const glm::vec3 &GetCameraPosition() const { return m_CameraPosition; }
        float GetCameraRotation() const { return m_CameraRotation; }

        void SetCameraPosition(const glm::vec3 &position);
        void SetCameraRotation(float rotation);

        void OnUpdate(float timestep);
        void OnEvent(Event &event);

    private:
        void OnKeyPressed();
        void OnMouseScrolled();

    private:
        glm::vec3 m_CameraPosition;
        float m_CameraRotation;
        float m_MovementSpeed;
        float m_AspectRatio;
        float m_ZoomLevel = 1.0f;
        std::shared_ptr<OrthographicCamera> m_Camera;
    };
}
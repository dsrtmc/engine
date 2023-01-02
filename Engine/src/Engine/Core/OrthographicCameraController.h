#pragma once

#include "Event.h"
#include "MouseEvent.h"
#include "OrthographicCamera.h"

#include <glm/glm.hpp>

namespace Engine
{
    class OrthographicCameraController
    {
    public:
        explicit OrthographicCameraController(float aspectRatio);
        ~OrthographicCameraController();

        [[nodiscard]] std::shared_ptr<OrthographicCamera> GetCamera() const { return m_Camera; }
        [[nodiscard]] const glm::vec3 &GetCameraPosition() const { return m_CameraPosition; }
        [[nodiscard]] float GetCameraRotation() const { return m_CameraRotation; }
        [[nodiscard]] float GetZoomLevel() const { return m_ZoomLevel; }

        void SetCameraPosition(const glm::vec3 &position);
        void SetCameraRotation(float rotation);
        void SetMovementSpeed(float speed);
        void SetAspectRatio(float ratio);
        void SetZoomLevel(float level);

        void OnUpdate(float timestep);
        void OnEvent(Event &event);

    private:
        void OnKeyPressed(KeyPressedEvent &event);
        void OnMouseScrolled(MouseScrolledEvent &event);

    private:
        glm::vec3 m_CameraPosition;
        float m_CameraRotation;
        float m_MovementSpeed;
        float m_AspectRatio;
        float m_ZoomLevel = 1.0f;
        std::shared_ptr<OrthographicCamera> m_Camera;
    };
}
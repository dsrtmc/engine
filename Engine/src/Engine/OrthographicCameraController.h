#pragma once

#include "OrthographicCamera.h"
#include "Event.h"

#include <glm/glm.hpp>

namespace Engine
{
    class OrthographicCameraController
    {
    public:
        OrthographicCameraController(float width, float height);
        ~OrthographicCameraController();

        const OrthographicCamera &GetCamera() const { return m_Camera; }
        const glm::vec3 &GetPosition() const { return m_Position; }

        void SetPosition(const glm::vec3 &position);

        void OnEvent(Event &event);

    private:
        OrthographicCamera m_Camera;
        glm::vec3 m_Position;
    };
}
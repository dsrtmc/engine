#pragma once

#include "Event.h"
#include "KeyEvent.h"

#include <glm/glm.hpp>

namespace Engine
{
    class OrthographicCamera
    {
    public:
        OrthographicCamera(float left, float right, float bottom, float top);
        ~OrthographicCamera();

        void OnUpdate();
        void OnEvent(Event &event);

        const glm::mat4 &GetViewMatrix() const { return m_ViewMatrix; }
        const glm::mat4 &GetProjectionMatrix() const { return m_ProjectionMatrix; }

        void SetPosition(const glm::vec3 &position);

    private:
        void UpdateViewMatrix(const glm::vec3 &position);

    private:
        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ProjectionMatrix;
    };
}
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

        const glm::mat4 &GetViewMatrix() const { return m_ViewMatrix; }
        const glm::mat4 &GetProjectionMatrix() const { return m_ProjectionMatrix; }
        const glm::vec3 &GetPosition() const { return m_Position; };
        float GetRotation() const { return m_Rotation; };

        void SetProjectionMatrix(const glm::mat4 &projection);
        void SetPosition(const glm::vec3 &position);
        void SetRotation(float rotation);

    private:
        void UpdateViewMatrix();

    private:
        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ProjectionMatrix;
        glm::vec3 m_Position;
        float m_Rotation;
    };
}
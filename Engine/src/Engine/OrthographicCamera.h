#pragma once

#include <glm/glm.hpp>

namespace Engine
{
    class OrthographicCamera
    {
    public:
        OrthographicCamera(float left, float right, float bottom, float top);
        ~OrthographicCamera();

        void OnUpdate();

        const glm::vec3 &GetPosition() const { return m_Position; }
        const glm::mat4 &GetViewMatrix() const { return m_ViewMatrix; }
        const glm::mat4 &GetProjectionMatrix() const { return m_ProjectionMatrix; }

        void SetPosition(const glm::vec3 &position);

    private:
        void UpdateViewMatrix();

    private:
        glm::vec3 m_Position;
        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ProjectionMatrix;
    };
}
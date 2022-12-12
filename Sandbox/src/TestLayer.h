#pragma once

#include "Engine.h"

class TestLayer : public Engine::Layer
{
public:
    TestLayer();
    ~TestLayer();

    void OnImGuiUpdate() override;
    void OnUpdate(float timestep) override;

    void OnEvent(Engine::Event &event) override;
    void OnKeyPressed(Engine::KeyPressedEvent &event);
    void OnWindowResized(Engine::WindowResizeEvent &event);

private:
    std::shared_ptr<Engine::VertexArray> m_VertexArray;
    std::shared_ptr<Engine::VertexArray> m_TriangleVAO;
    std::shared_ptr<Engine::Texture> m_Texture;
    std::shared_ptr<Engine::Shader> m_Shader;
    std::shared_ptr<Engine::Shader> m_TriangleShader;
    Engine::OrthographicCameraController m_CameraController;

private:
    bool m_UseTexture = false;
    glm::vec3 m_TriangleColor = glm::vec3(0.8f, 0.2f, 0.2f);
};
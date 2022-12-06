#pragma once

#include "Engine.h"

class TestLayer : public Engine::Layer
{
public:
    TestLayer();
    ~TestLayer();

    void OnImGuiUpdate() override;
    void OnUpdate() override;

private:
    std::shared_ptr<Engine::VertexArray> m_VertexArray;
    std::shared_ptr<Engine::Texture> m_Texture;
    std::shared_ptr<Engine::Shader> m_Shader;

private:
    bool m_UseTexture = true;
    glm::vec3 m_TriangleColor = glm::vec3(0.8f, 0.2f, 0.2f);
};
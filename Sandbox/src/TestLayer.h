#pragma once

#include "Engine.h"

class TestLayer : public Engine::Layer
{
public:
    TestLayer();
    ~TestLayer();

    void OnUpdate() override;

private:
    std::shared_ptr<Engine::VertexArray> m_VertexArray;
    std::shared_ptr<Engine::Texture> m_Texture;
    std::unique_ptr<Engine::Shader> m_Shader;
};
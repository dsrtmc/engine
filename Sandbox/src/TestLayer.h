#pragma once

#include "Engine.h"

class TestLayer : public Engine::Layer
{
public:
    TestLayer();
    ~TestLayer();

    void OnImGuiRender();
    void OnUpdate() override;

private:
    // VertexArray *m_VertexArray;
};
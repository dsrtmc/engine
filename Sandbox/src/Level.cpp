#include "Level.h"

#include <cmath>

Level::Level(const std::string &name)
    : m_Name(name)
{
    m_Stones.push_back(Stone({ -3.0f, 0.5f, 0.0f }));
    ENG_TRACE("Created Level");
}

Level::~Level()
{
    ENG_TRACE("Destroyed level");
}

void Level::OnUpdate(float timestep)
{
    for (auto stone : m_Stones)
        stone.OnUpdate(timestep);

    Engine::Renderer2D::DrawQuad({ -1.0f, 0.0f, 0.0f }, { 1.5f, 1.0f }, { 0.5f, 0.6f, 0.5f, 1.0f });
    Engine::Renderer2D::DrawQuad({ 0.0f, -1.0f, 0.0f }, { 2.0f, 1.0f }, { 0.2f, 0.3f, 0.8f, 1.0f });
}

bool Level::TestCollision(const glm::vec3 &position)
{
    std::vector<glm::vec3> defaultVertices = {
        { -0.5f, -0.5f, 0.0f },
        {  0.5f, -0.5f, 0.0f },
        {  0.5f,  0.5f, 0.0f },
        { -0.5f,  0.5f, 0.0f }
    };
    for (auto stone : m_Stones)
    {
        float xdiff = std::abs(position.x - stone.GetPosition().x);
        float ydiff = std::abs(position.y - stone.GetPosition().y);
        ENG_INFO("xdiff, ydiff: {0}, {1}", xdiff, ydiff);
        if (xdiff <= stone.GetSize().x && ydiff <= stone.GetSize().y)
            return true;
    }
    return false;
}

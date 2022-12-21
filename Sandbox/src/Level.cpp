#include "Level.h"

#include <cmath>

Level::Level(const std::string &name)
    : m_Name(name)
{
    m_Rocks.push_back(Rock({ -3.0f, 0.5f, 0.0f }));
    m_Rocks.push_back(Rock({ -1.0f, -1.5f, 0.0f }));
    ENG_TRACE("Created Level");
}

Level::~Level()
{
    ENG_TRACE("Destroyed level");
}

void Level::OnUpdate(float timestep)
{
}

void Level::OnRender()
{
    for (auto rock : m_Rocks)
        rock.OnRender();

    Engine::Renderer2D::DrawQuad({ -1.0f, 0.0f, 0.0f }, { 1.5f, 1.0f }, { 0.5f, 0.6f, 0.5f, 1.0f });
    Engine::Renderer2D::DrawQuad({ 0.0f, -1.0f, 0.0f }, { 2.0f, 1.0f }, { 0.2f, 0.3f, 0.8f, 1.0f });
}

/* Returns { -1, -1 } if there's a collision on the specified location, otherwise returns distance required to create a collision */
glm::vec2 Level::TestCollision(const glm::vec3 &position, const glm::vec2 &entitySize)
{
    glm::vec2 closestRock = { 0.0f, 0.0f };
    if (!m_Rocks.empty())
    {
        auto pos = m_Rocks[0].GetPosition();
        closestRock = { pos.x, pos.y };
    }
    for (auto rock : m_Rocks)
    {
        glm::vec2 rockPos = rock.GetPosition();
        // a² + b² == c²
        if (std::pow(position.x - rockPos.x, 2) + std::pow(position.y - rockPos.y, 2) < std::pow(position.x - closestRock.x, 2) + std::pow(position.y - closestRock.y, 2))
            closestRock = rockPos;

        float xdiff = std::abs(position.x - rockPos.x) - (entitySize.x / 2);
        float ydiff = std::abs(position.y - rockPos.y) - (entitySize.y / 2);

        // There is a collision on our next move - return the smallest step you can take to get a collision
        if (xdiff <= rock.GetSize().x / 2 && ydiff <= rock.GetSize().y / 2)
        {
            glm::vec2 result = glm::vec2(0.0f);
            result.x = std::max(0.0f, std::abs(position.x - closestRock.x) - rock.GetSize().x / 2 - entitySize.x / 2);
            result.y = std::max(0.0f, std::abs(position.y - closestRock.y) - rock.GetSize().y / 2 - entitySize.y / 2);
            return result;
        }
    }

    Engine::Renderer2D::DrawLine(position, glm::vec3(closestRock, 1.0f), { 1.0f, 0.2f, 0.3f, 1.0f });
    // No collision
    return { -1, -1 };
}
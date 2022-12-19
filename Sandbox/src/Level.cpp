#include "Level.h"

#include <cmath>

Level::Level(const std::string &name)
    : m_Name(name)
{
    m_Rocks.push_back(Rock({ -3.0f, 0.5f, 0.0f }));
    ENG_TRACE("Created Level");
}

Level::~Level()
{
    ENG_TRACE("Destroyed level");
}

void Level::OnUpdate(float timestep)
{
    for (auto rock : m_Rocks)
        rock.OnUpdate(timestep);

    Engine::Renderer2D::DrawQuad({ -1.0f, 0.0f, 0.0f }, { 1.5f, 1.0f }, { 0.5f, 0.6f, 0.5f, 1.0f });
    Engine::Renderer2D::DrawQuad({ 0.0f, -1.0f, 0.0f }, { 2.0f, 1.0f }, { 0.2f, 0.3f, 0.8f, 1.0f });
}

bool Level::TestCollision(const glm::vec3 &position, const glm::vec2 &entitySize)
{
    std::vector<glm::vec3> defaultVertices = {
        { -0.5f, -0.5f, 0.0f },
        {  0.5f, -0.5f, 0.0f },
        {  0.5f,  0.5f, 0.0f },
        { -0.5f,  0.5f, 0.0f }
    };
    for (auto rock : m_Rocks)
    {
        float xdiff = std::abs(position.x - rock.GetPosition().x) - (entitySize.x / 2);
        float ydiff = std::abs(position.y - rock.GetPosition().y) - (entitySize.y / 2);
        std::cout << "Player position: (" << position.x << ", " << position.y << ", " << position.z << ");" << std::endl;
        ENG_INFO("xdiff, ydiff: {0}, {1}", xdiff, ydiff);
        // TODO: do not hardcore the player's size
        if (xdiff <= (rock.GetSize().x / 2) && ydiff <= (rock.GetSize().y / 2))
            return true;
    }
    return false;
}

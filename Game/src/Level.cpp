#include "Level.h"

#include <cmath>

std::vector<std::string> tilemap = {
    ".................",
    "...XXX.....XXX...",
    "...X.........X...",
    "...X.........X...",
    "......XX.XX......",
    "......X...X......",
    "......XX.XX......",
    "...X.........X...",
    "...X.........X...",
    "...XXX.....XXX...",
    "................."
};

Level::Level(const std::string &name)
    : m_Name(name)
{
    m_RockTexture = std::make_shared<Engine::Texture2D>("../../Sandbox/assets/textures/cobblestone.png");
    m_WoodTexture = std::make_shared<Engine::Texture2D>("../../Sandbox/assets/textures/wood.png");
    size_t height = tilemap.size();
    size_t width = tilemap[0].size();
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (tilemap[i][j] == '.')
            {
                // TODO: write Wood::Size() (?) instead of hard-coding * 0.3f
                m_WoodBlocks.push_back(Wood({ j * 0.3f, (float)(1 - i) * 0.3f, -0.5f }, m_WoodTexture));
            }
            else if (tilemap[i][j] == 'X')
            {
                // TODO: write Rock::Size() (?) instead of hard-coding * 0.3f
                m_Rocks.push_back(Rock({ j * 0.3f, (float)(1 - i) * 0.3f, 0.0f }, m_RockTexture));
            }
        }
    }
    // Top left corner's tile's origin is {0, 0.3}
    // TODO: Change 0.15f to Rock::Size() (?) / 2
    m_Bounds[0] = { 0.0f - 0.15f,                       0.3f + 0.15f                        }; // top left
    m_Bounds[1] = { 0.0f - 0.15f + (float)width * 0.3f, 0.3f + 0.15f                        }; // top right
    m_Bounds[2] = { 0.0f - 0.15f + (float)width * 0.3f, 0.3f + 0.15f - (float)height * 0.3f }; // bottom right
    m_Bounds[3] = { 0.0f - 0.15f,                       0.3f + 0.15f - (float)height * 0.3f }; // bottom left
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

    for (auto wood : m_WoodBlocks)
        wood.OnRender();

    for (const auto &bound : m_Bounds)
        Engine::Renderer2D::DrawQuad({ bound.x, bound.y, 0.5f }, { 0.05f, 0.05f }, { 1.0f, 0.0f, 0.0f, 1.0f });
}

/* The logic here is much simpler than in the TestCollision, since it only returns a boolean rather than the required distance */
bool Level::IsOutOfBounds(const glm::vec3 &position, const glm::vec2 &entitySize)
{
    bool result = false;
    if (position.x - entitySize.x / 2 <= m_Bounds[0].x || // left
        position.x + entitySize.x / 2 >= m_Bounds[1].x || // right
        position.y + entitySize.y / 2 >= m_Bounds[0].y || // top
        position.y - entitySize.y / 2 <= m_Bounds[2].y)   // bottom
        result = true;
    return result;
}

/* Returns { -1, -1 } if there's a collision on the specified location, otherwise returns distance required to create a collision */
glm::vec2 Level::TestCollision(const glm::vec3 &position, const glm::vec2 &entitySize)
{
    if (!IsOutOfBounds(position, entitySize))
    {
        glm::vec2 closestRock = { 0.0f, 0.0f };
        if (!m_Rocks.empty())
        {
            auto pos = m_Rocks[0].GetPosition();
            closestRock = { pos.x, pos.y };
        }
        for (const auto &rock : m_Rocks)
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
                auto result = glm::vec2(0.0f);
                result.x = std::max(0.0f, std::abs(position.x - closestRock.x) - rock.GetSize().x / 2 - entitySize.x / 2);
                result.y = std::max(0.0f, std::abs(position.y - closestRock.y) - rock.GetSize().y / 2 - entitySize.y / 2);
                return result;
            }
        }

        Engine::Renderer2D::DrawLine(position, glm::vec3(closestRock, 1.0f), { 1.0f, 0.2f, 0.3f, 1.0f });
        // No collision
        return { -1, -1 };
    }
    return { 0.0f, 0.0f };
}

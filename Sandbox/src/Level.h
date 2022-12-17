#pragma once

#include "Engine.h"

class Stone
{
public:
    Stone(const glm::vec3 &position)
        : m_Position(position) {}

    ~Stone() {}

    void OnUpdate(float timestep)
    {
        Engine::Renderer2D::DrawQuad(m_Position, { 0.2f, 0.2f }, { 0.2f, 0.2f, 0.2f, 1.0f });
    }

    inline const glm::vec3 &GetPosition() const { return m_Position; }
    inline const glm::vec2 GetSize() const { return { 0.2f, 0.2f }; }

private:
    glm::vec3 m_Position;
};

class Level
{
public:
    Level(const std::string &name);
    ~Level();

    void OnUpdate(float timestep);
    bool TestCollision(const glm::vec3 &position);

private:
    std::string m_Name;
    std::vector<Stone> m_Stones;
};
#pragma once

#include "Engine.h"

class Rock
{
public:
    Rock(const glm::vec3 &position)
        : m_Position(position)
    {
        m_Texture = std::make_shared<Engine::Texture2D>("../../Sandbox/assets/textures/cobblestone.png");
    }

    ~Rock() {}

    void OnUpdate(float timestep) {}
    void OnRender()
    {
        Engine::Renderer2D::DrawQuad(m_Position, { 0.5f, 0.5f }, m_Texture, { 1.0f, 1.0f, 1.0f, 1.0f });
    }

    inline const glm::vec3 &GetPosition() const { return m_Position; }
    inline const glm::vec2 GetSize() const { return { 0.5f, 0.5f }; }

private:
    glm::vec3 m_Position;
    std::shared_ptr<Engine::Texture2D> m_Texture;
};

class Level
{
public:
    Level(const std::string &name);
    ~Level();

    void OnUpdate(float timestep);
    void OnRender();
    glm::vec2 TestCollision(const glm::vec3 &position, const glm::vec2 &entitySize);

private:
    std::string m_Name;
    std::vector<Rock> m_Rocks;
};
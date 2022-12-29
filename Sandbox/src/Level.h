#pragma once

#include "Engine.h"

/* ------------ Rock ------------ */
class Rock
{
public:
    explicit Rock(const glm::vec3 &position)
        : m_Position(position), m_Size({ 0.3f, 0.3f })
    {
        m_Texture = std::make_shared<Engine::Texture2D>("../../Sandbox/assets/textures/cobblestone.png");
    }
    ~Rock() = default;

    void OnUpdate(float timestep) {}
    void OnRender()
    {
        Engine::Renderer2D::DrawQuad(m_Position, m_Size, m_Texture, { 1.0f, 1.0f, 1.0f, 1.0f });
    }

    [[nodiscard]] inline const glm::vec3 &GetPosition() const { return m_Position; }
    [[nodiscard]] inline const glm::vec2 &GetSize() const { return m_Size; }

private:
    glm::vec3 m_Position;
    glm::vec2 m_Size;
    std::shared_ptr<Engine::Texture2D> m_Texture;
};

/* ------------ Wood ------------ */
class Wood
{
public:
    explicit Wood(const glm::vec3 &position)
        : m_Position(position), m_Size({ 0.3f, 0.3f })
    {
        m_Texture = std::make_shared<Engine::Texture2D>("../../Sandbox/assets/textures/wood.png");
    }
    ~Wood() = default;

    void OnUpdate(float timestep) {}
    void OnRender()
    {
        Engine::Renderer2D::DrawQuad(m_Position, m_Size, { 0.4f, 0.305f, 0.227f, 1.0f });
//        Engine::Renderer2D::DrawQuad(m_Position, m_Size, m_Texture, { 1.0f, 1.0f, 1.0f, 1.0f });
    }

    [[nodiscard]] inline const glm::vec3 &GetPosition() const { return m_Position; }
    [[nodiscard]] inline const glm::vec2 &GetSize() const { return m_Size; }

private:
    glm::vec3 m_Position;
    glm::vec2 m_Size;
    std::shared_ptr<Engine::Texture2D> m_Texture;
};

/* ------------ Level ------------ */
class Level
{
public:
    explicit Level(const std::string &name);
    ~Level();

    void OnUpdate(float timestep);
    void OnRender();
    glm::vec2 TestCollision(const glm::vec3 &position, const glm::vec2 &entitySize);

private:
    std::string m_Name;
    std::vector<Rock> m_Rocks;
    std::vector<Wood> m_WoodBlocks;
};
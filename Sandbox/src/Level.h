#pragma once

#include "Engine.h"

/* ------------ Rock ------------ */
class Rock
{
public:
    explicit Rock(const glm::vec3 &position, std::shared_ptr<Engine::Texture2D> texture)
        : m_Position(position), m_Size({ 0.3f, 0.3f }), m_Texture(texture) {}
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
    explicit Wood(const glm::vec3 &position, std::shared_ptr<Engine::Texture2D> texture)
        : m_Position(position), m_Size({ 0.3f, 0.3f }), m_Texture(texture) {}
    ~Wood() = default;

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
    std::shared_ptr<Engine::Texture2D> m_RockTexture;
    std::shared_ptr<Engine::Texture2D> m_WoodTexture;
    std::vector<Rock> m_Rocks;
    std::vector<Wood> m_WoodBlocks;
};
#pragma once

#include "Engine.h"
#include "Level.h"

#include <glm/glm.hpp>

class Player
{
public:
    Player(const glm::vec3 &position, Level *level);
    ~Player();

    void OnUpdate(float timestep);
    void OnEvent(Engine::Event &event);

    void OnKeyPressed(Engine::KeyPressedEvent &event);

    inline void SetPosition(const glm::vec3 &position) { m_Position = position; }

    inline const glm::vec3 &GetPosition() const { return m_Position; }
    inline const std::vector<glm::vec3> &GetVertices() const { return m_Vertices; }

private:
    glm::vec3 m_Position;
    std::vector<glm::vec3> m_Vertices;
    std::shared_ptr<Engine::Texture2D> m_Texture;
    Level *m_Level;
};
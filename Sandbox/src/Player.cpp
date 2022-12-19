#include "Player.h"

Player::Player(const glm::vec3 &position, const glm::vec2 &size, Level *level)
    : m_Position(position), m_Size(size), m_Level(level)
{
    m_Texture = std::make_shared<Engine::Texture2D>("../Sandbox/assets/textures/pirate.png");

    std::vector<glm::vec3> defaultVertices = {
        { -0.5f, -0.5f, 0.0f },
        {  0.5f, -0.5f, 0.0f },
        {  0.5f,  0.5f, 0.0f },
        { -0.5f,  0.5f, 0.0f }
    };

    m_Vertices.clear();
    for (auto vertex : defaultVertices)
        m_Vertices.push_back(vertex + m_Position);

    ENG_TRACE("Created Player");
}

Player::~Player()
{
    ENG_TRACE("Destroyed Player");
}

void Player::OnUpdate(float timestep)
{
    glm::vec3 position = m_Position;
    if (Engine::Input::IsKeyPressed(ENG_KEY_W))
    {
        glm::vec3 npos = position;
        npos.y += 1.5f * timestep;
        if (!m_Level->TestCollision(npos, m_Size))
            position.y = npos.y;
    }
    if (Engine::Input::IsKeyPressed(ENG_KEY_S))
    {
        glm::vec3 npos = position;
        npos.y -= 1.5f * timestep;
        if (!m_Level->TestCollision(npos, m_Size))
            position.y = npos.y;
    }
    if (Engine::Input::IsKeyPressed(ENG_KEY_A))
    {
        glm::vec3 npos = position;
        npos.x -= 1.5f * timestep;
        if (!m_Level->TestCollision(npos, m_Size))
            position.x = npos.x;
    }
    if (Engine::Input::IsKeyPressed(ENG_KEY_D))
    {
        glm::vec3 npos = position;
        npos.x += 1.5f * timestep;
        if (!m_Level->TestCollision(npos, m_Size))
            position.x = npos.x;
    }

    // NOTE: kinda dependent on the framerate right now, no idea how to fix as of yet
    m_Position = position;

    Engine::Renderer2D::DrawQuad(m_Position, m_Size, m_Texture);

    std::vector<glm::vec3> defaultVertices = {
        { -0.5f, -0.5f, 0.0f },
        {  0.5f, -0.5f, 0.0f },
        {  0.5f,  0.5f, 0.0f },
        { -0.5f,  0.5f, 0.0f }
    };

    m_Vertices.clear();
    for (auto vertex : defaultVertices)
        m_Vertices.push_back(vertex + m_Position);
    // ENG_INFO("Bottom left vertex: ({0}, {1}, {2})", m_Vertices[0].x, m_Vertices[1].y, m_Vertices[2].z);
}

void Player::OnEvent(Engine::Event &event)
{
    if (event.GetType() == Engine::EventType::KeyPressed)
        OnKeyPressed((Engine::KeyPressedEvent &)event);
}

void Player::OnKeyPressed(Engine::KeyPressedEvent &event)
{
}

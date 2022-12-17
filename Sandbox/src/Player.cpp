#include "Player.h"

Player::Player(const glm::vec3 &position, Level *level)
    : m_Position(position), m_Level(level)
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
        position.y += 1.5f * timestep;
    if (Engine::Input::IsKeyPressed(ENG_KEY_S))
        position.y -= 1.5f * timestep;
    if (Engine::Input::IsKeyPressed(ENG_KEY_A))
        position.x -= 1.5f * timestep;
    if (Engine::Input::IsKeyPressed(ENG_KEY_D))
        position.x += 1.5f * timestep;

    if (!m_Level->TestCollision(position))
        m_Position = position;

    float aspectRatio = (float)m_Texture->GetWidth() / (float)m_Texture->GetHeight();
    Engine::Renderer2D::DrawQuad(m_Position, { 0.25f * aspectRatio, 0.25f }, m_Texture);

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

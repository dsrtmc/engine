#include "Player.h"

Player::Player(const glm::vec3 &position, const glm::vec2 &size, Level *level)
    : m_Position(position), m_Size(size), m_Level(level)
{
    m_Texture = std::make_shared<Engine::Texture2D>("../../Sandbox/assets/textures/pirate.png");

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

    /* TODO: Fix the bug - as of right now, there is a bug that causes the entity to move within
     * 2px inside/outside of the actual tile border; I believe that has something to do with the
     * floating point imprecision, however it's just my best guess */
    
    if (Engine::Input::IsKeyPressed(ENG_KEY_W))
    {
        glm::vec3 npos = position;
        npos.y += 1.5f * timestep;

        glm::vec2 result = m_Level->TestCollision(npos, m_Size);
        if (result.x != -1 && result.y != -1)
            position.y += std::min(1.5f, result.y);
        else
            position.y = npos.y;
    }
    if (Engine::Input::IsKeyPressed(ENG_KEY_S))
    {
        glm::vec3 npos = position;
        npos.y -= 1.5f * timestep;

        glm::vec2 result = m_Level->TestCollision(npos, m_Size);
        if (result.x != -1 && result.y != -1)
            position.y -= std::min(1.5f, result.y);
        else
            position.y = npos.y;
    }
    if (Engine::Input::IsKeyPressed(ENG_KEY_A))
    {
        glm::vec3 npos = position;
        npos.x -= 1.5f * timestep;

        glm::vec2 result = m_Level->TestCollision(npos, m_Size);
        if (result.x != -1 && result.y != -1)
            position.x -= std::min(1.5f, result.x);
        else
            position.x = npos.x;
    }
    if (Engine::Input::IsKeyPressed(ENG_KEY_D))
    {
        glm::vec3 npos = position;
        npos.x += 1.5f * timestep;

        glm::vec2 result = m_Level->TestCollision(npos, m_Size);
        if (result.x != -1 && result.y != -1)
            position.x += std::min(1.5f, result.x);
        else
            position.x = npos.x;
    }
    m_Position = position;


    // std::vector<glm::vec3> defaultVertices = {
    //     { -0.5f, -0.5f, 0.0f },
    //     {  0.5f, -0.5f, 0.0f },
    //     {  0.5f,  0.5f, 0.0f },
    //     { -0.5f,  0.5f, 0.0f }
    // };

    // m_Vertices.clear();
    // for (auto vertex : defaultVertices)
    //     m_Vertices.push_back(vertex + m_Position);
}

void Player::OnRender()
{
    ENG_TRACE("We are drawing the player: {0}", m_Texture->GetRendererID());
    Engine::Renderer2D::DrawQuad(m_Position, m_Size, m_Texture);
}

void Player::OnEvent(Engine::Event &event)
{
    if (event.GetType() == Engine::EventType::KeyPressed)
        OnKeyPressed((Engine::KeyPressedEvent &)event);
}

void Player::OnKeyPressed(Engine::KeyPressedEvent &event)
{
}

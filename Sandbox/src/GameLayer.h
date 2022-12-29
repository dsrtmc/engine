#pragma once

#include "Engine.h"
#include "Level.h"
#include "Player.h"

class GameLayer : public Engine::Layer
{
public:
    GameLayer();
    ~GameLayer() override;

    void OnImGuiUpdate() override;
    void OnUpdate(float timestep) override;

    void OnEvent(Engine::Event &event) override;
    void OnKeyPressed(Engine::KeyPressedEvent &event);
    void OnWindowResized(Engine::WindowResizeEvent &event);
    void OnMouseScrolled(Engine::MouseScrolledEvent &event);

private:
    Engine::OrthographicCameraController m_CameraController;
    Level *m_Level;
    Player *m_Player;

    // Profiling should not be here as well
    struct ProfilingResult
    {
        std::string name;
        double duration;
    };
    std::vector<ProfilingResult> m_ProfilingResults;
};
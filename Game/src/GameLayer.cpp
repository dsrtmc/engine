#include "GameLayer.h"

#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>

using namespace Engine;

/* Create a timer and add the profiling result to the other results once the scope ends */
#define PROFILING_SCOPE(tname) Timer timer__LINE__(tname, [&](const std::string &name, double duration)\
    { m_ProfilingResults.push_back({ name, duration });\
})

GameLayer::GameLayer()
    : Layer("Game layer"), m_CameraController(1440.0f / 900.0f), m_Level(new Level("Main Level")),
    m_Player(new Player({ 0.25f, 0.25f, 0.0f }, { 0.25f, 0.25f }, m_Level))
{
    Renderer2D::Initialize();
    ENG_TRACE("Created Game layer");
}

GameLayer::~GameLayer()
{
    Renderer2D::Shutdown();
    delete m_Level;
    delete m_Player;
    ENG_TRACE("Destroyed Game layer");
}

// Write Layer-specific ImGui code here
void GameLayer::OnImGuiUpdate()
{
    ImGui::Begin("General");

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

    for (auto &result : m_ProfilingResults)
        ImGui::Text("%.3fms %s", result.duration * 0.001, result.name.c_str());

    m_ProfilingResults.clear();
    ImGui::End();
}

void GameLayer::OnUpdate(float timestep)
{
    PROFILING_SCOPE("GameLayer::OnUpdate()");
    glClearColor(0.07f, 0.07f, 0.07f, 1.0f);
    Renderer::Clear();

    Renderer2D::BeginScene(m_CameraController.GetCamera());
    {
        PROFILING_SCOPE("Level & Player OnUpdate()");
        m_Level->OnUpdate(timestep);
        m_Player->OnUpdate(timestep);
    }
    m_CameraController.SetCameraPosition(m_Player->GetPosition());
    Renderer2D::EndScene();


    Renderer2D::BeginScene(m_CameraController.GetCamera());
    {
        PROFILING_SCOPE("Level & Player OnRender()");
        m_Level->OnRender();
        m_Player->OnRender();
    }
    Renderer2D::EndScene();
}

void GameLayer::OnEvent(Event &event)
{
    m_Player->OnEvent(event);

    if (event.GetType() == EventType::WindowResized)
        OnWindowResized((WindowResizeEvent &)event);

    if (event.GetType() == EventType::KeyPressed)
        OnKeyPressed((KeyPressedEvent &)event);

    if (event.GetType() == EventType::MouseScrolled)
        OnMouseScrolled((MouseScrolledEvent &)event);
}

void GameLayer::OnMouseScrolled(MouseScrolledEvent &event)
{
    m_CameraController.SetZoomLevel(m_CameraController.GetZoomLevel() - (float)event.GetYOffset() * 0.1f);
}

void GameLayer::OnKeyPressed(Engine::KeyPressedEvent &event)
{
}

void GameLayer::OnWindowResized(Engine::WindowResizeEvent &event)
{
    float aspectRatio = (float) event.GetWidth() / (float) event.GetHeight();
    float zoomLevel = m_CameraController.GetZoomLevel();

    m_CameraController.SetAspectRatio(aspectRatio);
    m_CameraController.GetCamera()->SetProjectionMatrix(glm::ortho(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel, -1.0f, 1.0f));
}
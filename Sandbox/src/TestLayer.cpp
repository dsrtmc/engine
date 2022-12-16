#include "TestLayer.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace Engine;

TestLayer::TestLayer()
    : Layer("Test layer"), m_CameraController(1440.0f / 900.0f)
{
    m_ContainerTexture = std::make_shared<Texture2D>("../Sandbox/assets/textures/container.jpg");
    Renderer2D::Initialize();
    ENG_TRACE("Created Test layer");
}

TestLayer::~TestLayer()
{
    Renderer2D::Shutdown();
    ENG_TRACE("Destroyed Test layer");
}

// Write Layer-specific ImGui code here
void TestLayer::OnImGuiUpdate()
{
    // General settings
    ImGui::Begin("Settings");
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();

    // Camera settings
    auto camera = m_CameraController.GetCamera();
    ImGui::Begin("Camera");

    // Camera movement
    glm::vec3 position = m_CameraController.GetCameraPosition();
    float bound = ((float)1440 / (float)900) * 1.0f;
    ImGui::SliderFloat("Camera X:", &position.x, -bound, bound);
    ImGui::SliderFloat("Camera Y:", &position.y, -1.0f, 1.0f);

    m_CameraController.SetCameraPosition(position);

    if (ImGui::Button("Reset"))
        m_CameraController.SetCameraPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    
    // Camera zoom
    float zoom = m_CameraController.GetZoomLevel();
    ImGui::SliderFloat("Zoom level:", &zoom, -5.0f, 10.0f);
    m_CameraController.SetZoomLevel(zoom);

    glm::mat4 VP = camera->GetProjectionMatrix() * camera->GetViewMatrix();

    // Profiling
    for (auto &result : m_ProfilingResults)
    {
        ImGui::Text("%.3fms %s", result.duration * 0.001, result.name.c_str());
    }
    m_ProfilingResults.clear();

    ImGui::End();
}

void TestLayer::OnUpdate(float timestep)
{
    Timer timer("TestLayer::OnUpdate");
    glClearColor(0.07f, 0.07f, 0.07f, 1.0f);
    Renderer::Clear();

    m_CameraController.OnUpdate(timestep);

    Renderer2D::BeginScene(m_CameraController.GetCamera());
    Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, m_ContainerTexture);
    Renderer2D::EndScene();

    // Draw a grid of quads
    {
        Timer timer("Renderer2D 144 draw calls");
        Renderer2D::BeginScene(m_CameraController.GetCamera());
        for (int col = 0; col < 12; col++)
        {
            for (int row = 0; row < 12; row++)
            {
                glm::vec3 pos(row * 0.11f, col * 0.11f, 0.0f);
                Renderer2D::DrawQuad(pos, { 0.1f, 0.1f }, { 0.8f, 0.3f, 0.5f, 1.0f });
            }
        }
        Renderer2D::EndScene();
        m_ProfilingResults.push_back({ timer.GetName(), timer.GetDuration() });
    }

    Renderer2D::BeginScene(m_CameraController.GetCamera());
    Renderer2D::DrawQuad({ -1.0f, 1.0f, 0.0f }, { 0.5f, 0.5f }, { 0.3f, 0.8f, 0.7f, 1.0f });
    Renderer2D::EndScene();
    m_ProfilingResults.push_back({ timer.GetName(), timer.GetDuration() });
}

void TestLayer::OnEvent(Event &event)
{
    m_CameraController.OnEvent(event);

    if (event.GetType() == EventType::WindowResized)
        OnWindowResized((WindowResizeEvent &)event);

    if (event.GetType() == EventType::KeyPressed)
        OnKeyPressed((KeyPressedEvent &)event);
}

void TestLayer::OnKeyPressed(Engine::KeyPressedEvent &event)
{
}

void TestLayer::OnWindowResized(Engine::WindowResizeEvent &event)
{
    float aspectRatio = (float) event.GetWidth() / (float) event.GetHeight();
    float zoomLevel = m_CameraController.GetZoomLevel();
    // I don't think it works as intended as of right now
    m_CameraController.GetCamera()->SetProjectionMatrix(glm::ortho(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel, -1.0f, 1.0f));
}
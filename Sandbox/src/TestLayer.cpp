#include "TestLayer.h"

#include <imgui.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace Engine;

// Create a timer and add the profiling result to the other results once the scope ends
#define PROFILING_SCOPE(tname) Timer timer__LINE__(tname, [&](const std::string &name, double duration)\
    { m_ProfilingResults.push_back({ name, duration });\
})

TestLayer::TestLayer()
    : Layer("Test layer"), m_CameraController(1440.0f / 900.0f)
{
    m_ContainerTexture = std::make_shared<Texture2D>("../../Sandbox/assets/textures/container.jpg");

    FramebufferProperties framebufferProps = { 1440, 900 };
    m_Framebuffer = std::make_shared<Framebuffer>(framebufferProps);

    m_GridColor = glm::vec4(0.015f, 0.2f, 0.5f, 1.0f);
    m_Size = glm::vec2(0.1f, 0.1f);

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
    ImGui::ColorEdit3("Grid color:", glm::value_ptr(m_GridColor));
    ImGui::DragFloat2("Size:", glm::value_ptr(m_Size), 0.01f, 0.0f, 1.0f);
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
    unsigned int textureID = m_Framebuffer->GetColorAttachmentID();
    ImGui::Image((void *)textureID, ImVec2(432.0f, 270.0f), ImVec2(0, 1), ImVec2(1, 0));
    ImGui::End();

    ImGui::ShowDemoWindow();
}

void TestLayer::OnUpdate(float timestep)
{
    PROFILING_SCOPE("TestLayer::OnUpdate");
    m_Framebuffer->Bind();
    glClearColor(0.07f, 0.07f, 0.07f, 1.0f);
    Renderer::Clear();

    m_CameraController.OnUpdate(timestep);

    Renderer2D::BeginScene(m_CameraController.GetCamera());
    Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.99f }, { 0.5f, 0.5f }, { 0.2f, 0.6f, 0.8f, 1.0f });
    Renderer2D::DrawQuad({ -2.0f, 2.0f, 0.0f }, { 1.0f, 1.0f }, { 0.3f, 0.8f, 0.7f, 1.0f });
    Renderer2D::EndScene();

    Renderer2D::BeginScene(m_CameraController.GetCamera());
    Renderer2D::DrawQuad({ 2.0f, -2.0f, 0.0f }, { 1.0f, 1.0f }, { 0.3f, 0.8f, 0.7f, 1.0f });
    Renderer2D::DrawRotatedQuad({ 0.0f, -2.0f, 0.0f }, { 1.0f, 1.0f }, glm::radians(45.0f), { 0.3f, 0.8f, 0.9f, 1.0f });
    Renderer2D::DrawRotatedQuad({ 0.0f, 2.0f, -0.1f }, { 1.0f, 1.0f }, glm::radians(45.0f), m_ContainerTexture, { 0.5f, 0.5f, 0.5f, 1.0f });
    // TODO: FIX FIX FIX ^^^^^^^^^^^^^^^^^^ FIX FIX FIX IF XIF XIF XIF I
    Renderer2D::EndScene();

    {
        PROFILING_SCOPE("a lot of batched calls");
        Renderer2D::BeginScene(m_CameraController.GetCamera());
        for (int row = 0; row < 45; row++)
        {
            for (int col = 0; col < 100; col++)
            {
                glm::vec3 pos(col * 0.105f, row * 0.105f, 1.0f);
                Renderer2D::DrawQuad(pos, m_Size, { m_GridColor.r, row * 0.02f, col * 0.02f, 0.5f });
            }
        }
        Renderer2D::EndScene();
    }
    static float rotation = 0.0f;
    rotation += timestep * 50.0f;
    Renderer2D::BeginScene(m_CameraController.GetCamera());
    Renderer2D::DrawRotatedQuad({ 0.0f, 0.0f, 0.5f }, { 0.25f, 0.5f }, glm::radians(rotation), { 0.6f, 0.8f, 0.2f, 1.0f });
    Renderer2D::DrawRotatedQuad({ -1.0f, 1.0f, 0.0f }, { 0.5f, 0.25f }, glm::radians(45.0f), { 0.1f, 0.5f, 0.4f, 1.0f });
    Renderer2D::EndScene();

    Renderer2D::BeginScene(m_CameraController.GetCamera());
    Renderer2D::DrawLine({ -5.0f, 2.0f, 0.0f }, { -3.0f, -6.0f, 0.0f }, { 1.0f, 0.2f, 0.3f, 1.0f });
    Renderer2D::EndScene();
    m_Framebuffer->Unbind();
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
    m_CameraController.SetAspectRatio(aspectRatio);
    m_CameraController.GetCamera()->SetProjectionMatrix(glm::ortho(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel, -1.0f, 1.0f));
}
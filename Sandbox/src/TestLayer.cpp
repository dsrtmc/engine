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
    // typedef void (APIENTRY *GLDEBUGPROC)(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam);
    // Filepaths are relative from /build/
    m_Shader = Shader::FromTextFiles(
        "../Sandbox/assets/shaders/shader.vert.glsl",
        "../Sandbox/assets/shaders/shader.frag.glsl"
    );
    m_TriangleShader = Shader::FromTextFiles(
        "../Sandbox/assets/shaders/shader.vert.glsl",
        "../Sandbox/assets/shaders/triangle.frag.glsl"
    );

    m_TriangleShader->Bind();
    m_TriangleShader->SetUniformMatrix4fv("u_Transform", glm::mat4(1.0f));

    m_Shader->Bind();
    m_Shader->SetUniformMatrix4fv("u_Transform", glm::mat4(1.0f));

    m_Shader->SetUniform1i("u_UseTexture", m_UseTexture);
    m_Shader->SetUniform3fv("u_Color", m_TriangleColor);

    // Load a texture from a file then bind it to the first slot
    std::shared_ptr<Texture> container = std::make_shared<Texture>("../Sandbox/assets/textures/container.jpg");
    m_Texture = container;
    m_Texture->Bind(0);

    float vertices[] = {
        -0.5f, -0.5f, 0.0f, -1.0f, -1.0f, // bottom left
         0.5f, -0.5f, 0.0f,  1.0f, -1.0f, // bottom right
         0.5f,  0.5f, 0.0f,  1.0f,  1.0f, // top right
        -0.5f,  0.5f, 0.0f, -1.0f,  1.0f  // top left
    };

    GLuint indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    // Create a vertex array object
    std::shared_ptr<VertexArray> vao = std::make_shared<VertexArray>();
    vao->Bind();
    m_VertexArray = vao;

    // Specify a layout of our vertices
    BufferLayout layout;
    layout.Push(3); // vertex positions
    layout.Push(2); // texture coordinates

    // Create a vertex buffer object and bind it to the specified layout
    std::shared_ptr<VertexBuffer> vbo = std::make_shared<VertexBuffer>(vertices, sizeof(vertices));
    vbo->SetLayout(layout);

    // Create an index buffer object 
    std::shared_ptr<IndexBuffer> ibo = std::make_shared<IndexBuffer>(indices, sizeof(indices) / sizeof(GLuint));
    ibo->Bind();

    // Make the buffers the vertex array's private members, not used yet
    vao->SetVertexBuffer(vbo);
    vao->SetIndexBuffer(ibo);

    // Single quad data
    std::shared_ptr<VertexArray> triangleVAO = std::make_shared<VertexArray>();
    triangleVAO->Bind();
    BufferLayout triangleLayout;
    triangleLayout.Push(3);
    triangleLayout.Push(2);
    std::shared_ptr<VertexBuffer> triangleVBO = std::make_shared<VertexBuffer>(vertices, sizeof(vertices));
    triangleVBO->SetLayout(triangleLayout);
    std::shared_ptr<IndexBuffer> triangleIBO = std::make_shared<IndexBuffer>(indices, sizeof(indices) / sizeof(GLuint));
    ibo->Bind();
    triangleVAO->SetVertexBuffer(triangleVBO);
    triangleVAO->SetIndexBuffer(triangleIBO);

    m_TriangleVAO = triangleVAO;

    ENG_TRACE("Created Test layer");
}

TestLayer::~TestLayer()
{
    ENG_TRACE("Destroyed Test layer");
}

// Write Layer-specific ImGui code here
void TestLayer::OnImGuiUpdate()
{
    // General settings
    ImGui::Begin("Settings");

    m_Shader->Bind();
    ImGui::Checkbox("Use texture", &m_UseTexture);
    m_Shader->SetUniform1f("u_UseTexture", m_UseTexture);

    ImGui::ColorEdit3("Triangle color", glm::value_ptr(m_TriangleColor));
    m_Shader->SetUniform3fv("u_Color", m_TriangleColor);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();

    // Camera settings
    auto camera = m_CameraController.GetCamera();
    ImGui::Begin("Camera");

    glm::vec3 position = m_CameraController.GetCameraPosition();
    float bound = ((float)1440 / (float)900) * 1.0f;
    ImGui::SliderFloat("Camera X:", &position.x, -bound, bound);
    ImGui::SliderFloat("Camera Y:", &position.y, -1.0f, 1.0f);

    m_CameraController.SetCameraPosition(position);

    if (ImGui::Button("Reset"))
        m_CameraController.SetCameraPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    
    float zoom = m_CameraController.GetZoomLevel();
    ImGui::SliderFloat("Zoom level:", &zoom, -5.0f, 10.0f);
    m_CameraController.SetZoomLevel(zoom);

    glm::mat4 VP = camera->GetProjectionMatrix() * camera->GetViewMatrix();
    m_Shader->SetUniformMatrix4fv("u_VP", VP);
    m_TriangleShader->Bind();
    m_TriangleShader->SetUniformMatrix4fv("u_VP", VP);

    ImGui::End();
}

void TestLayer::OnUpdate(float timestep)
{
    glClearColor(0.07f, 0.07f, 0.07f, 1.0f);
    Renderer::Clear();

    // Place it in OnUpdate() for smooth camera movement, OnEvent() would treat is as press/repeat only
    m_CameraController.OnUpdate(timestep);

    // Draw a grid of textured quads
    for (int col = 0; col < 12; col++)
    {
        for (int row = 0; row < 12; row++)
        {
            glm::vec3 pos(row * 0.11f, col * 0.11f, 0.0f);
            glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * glm::scale(glm::mat4(1.0f), glm::vec3(0.1f, 0.1f, 0.1f));
            m_Shader->Bind();
            m_Shader->SetUniformMatrix4fv("u_Transform", transform);

            Renderer::Submit(m_VertexArray, m_Shader);
        }
    }
    Renderer::Submit(m_TriangleVAO, m_TriangleShader);
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
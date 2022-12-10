#include "TestLayer.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <glm/gtc/matrix_transform.hpp>

using namespace Engine;

TestLayer::TestLayer()
    : Layer("Test layer"), m_CameraController(1440, 900)
{
    // Filepaths are relative from /build/
    m_Shader = Shader::FromTextFiles(
        "../Sandbox/assets/shaders/shader.vert.glsl",
        "../Sandbox/assets/shaders/shader.frag.glsl"
    );
    m_Shader->Bind();

    m_Shader->SetUniform1i("u_UseTexture", m_UseTexture);
    m_Shader->SetUniform3fv("u_Color", m_TriangleColor);

    // Create view and projection matrices
    // m_Camera = std::make_shared<OrthographicCamera>(0.0f, 1440.0f, 0.0f, 900.0f);

    // Load a texture from a file then bind it to the first slot
    std::shared_ptr<Texture> container = std::make_shared<Texture>("../Sandbox/assets/textures/container.jpg");
    m_Texture = container;
    m_Texture->Bind(0);

    float vertices[] = {
        520.0f, 250.0f, 0.0f, -1.0f, -1.0f, 
         920.0f, 250.0f, 0.0f,  1.0f, -1.0f,
         920.0f,  650.0f, 0.0f,  1.0f,  1.0f,
        520.0f,  650.0f, 0.0f, -1.0f,  1.0f
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

    ImGui::Checkbox("Use texture", &m_UseTexture);
    m_Shader->SetUniform1f("u_UseTexture", m_UseTexture);

    ImGui::ColorEdit3("Triangle color", glm::value_ptr(m_TriangleColor));
    m_Shader->SetUniform3fv("u_Color", m_TriangleColor);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();

    // Camera settings
    OrthographicCamera camera = m_CameraController.GetCamera();
    ImGui::Begin("Camera");

    glm::vec3 position = m_CameraController.GetCameraPosition();
    ImGui::SliderFloat("Camera X:", &position.x, -720.0f, 720.0f);
    ImGui::SliderFloat("Camera Y:", &position.y, -450.0f, 450.0f);

    m_CameraController.SetCameraPosition(position);
    camera.SetPosition(position);

    if (ImGui::Button("Reset"))
        m_CameraController.SetCameraPosition(glm::vec3(0.0f, 0.0f, 0.0f));

    m_Shader->SetUniformMatrix4fv("u_VP", camera.GetProjectionMatrix() * camera.GetViewMatrix());

    ImGui::End();
}

void TestLayer::OnUpdate(float timestep)
{
    Renderer::Clear();

    // Place it in OnUpdate() for smooth camera movement, OnEvent() would treat is as press/repeat only
    m_CameraController.OnUpdate(timestep);

    // m_Shader->SetUniformMatrix4fv("u_Transform", glm::mat4(1.0f));
    // Renderer::Submit(m_VertexArray, m_Shader);
    // Draw a grid of textured quads
    for (int row = 0; row < 5; row++)
    {
        for (int col = 0; col < 5; col++)
        {
            glm::vec3 pos(row * 150.0f, col * 150.0f, 0.0f);
            glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * glm::scale(glm::mat4(1.0f), glm::vec3(0.35f, 0.35f, 1.0f));
            m_Shader->SetUniformMatrix4fv("u_Transform", transform);

            Renderer::Submit(m_VertexArray, m_Shader);
        }
    }
}

void TestLayer::OnEvent(Event &event)
{
    m_CameraController.OnEvent(event);
}

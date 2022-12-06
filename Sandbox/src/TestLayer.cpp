#include "TestLayer.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <glm/gtc/matrix_transform.hpp>

using namespace Engine;

TestLayer::TestLayer()
    : Layer("Test layer")
{
    // Filepaths are relative from /build/
    m_Shader = Shader::FromTextFiles(
        "../Sandbox/assets/shaders/shader.vert.glsl",
        "../Sandbox/assets/shaders/shader.frag.glsl"
    );
    m_Shader->Bind();

    m_Shader->SetUniform1i("u_UseTexture", m_UseTexture);
    m_Shader->SetUniform3fv("u_Color", m_TriangleColor);

    std::shared_ptr<Texture> container = std::make_shared<Texture>("../Sandbox/assets/textures/container.jpg");
    m_Texture = container;
    m_Texture->Bind(0);

    float vertices[] = {
        -0.5f, -0.5f, 0.0f, -1.0f, -1.0f,
         0.5f, -0.5f, 0.0f,  1.0f, -1.0f,
         0.5f,  0.5f, 0.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, 0.0f, -1.0f,  1.0f
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
    // 3 coordinates per attribute => one Push() call == one attribute
    layout.Push(3);
    layout.Push(2);

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
    ImGui::Begin("Test window");

    ImGui::Text("that is test text lol");

    ImGui::Checkbox("Use texture", &m_UseTexture);
    m_Shader->SetUniform1f("u_UseTexture", m_UseTexture);

    ImGui::ColorEdit3("Triangle color", glm::value_ptr(m_TriangleColor));
    m_Shader->SetUniform3fv("u_Color", m_TriangleColor);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
}

void TestLayer::OnUpdate()
{
    Renderer::Clear();
    m_VertexArray->Bind();

    for (int row = 0; row < 5; row++)
    {
        for (int col = 0; col < 5; col++)
        {
            glm::vec3 pos(row * 0.22f, col * 0.32f, 0.0f);
            glm::mat4 transform = glm::mat4(1.0f);
            transform = glm::translate(transform, glm::vec3(-0.45f, -0.6f, 0.0f));
            transform = glm::translate(transform, pos) * glm::scale(glm::mat4(1.0f), glm::vec3(0.2f, 0.3f, 1.0f));
            m_Shader->SetUniformMatrix4fv("u_Transform", transform);

            Renderer::Submit(m_VertexArray, m_Shader);
        }
    }
}
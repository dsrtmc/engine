#include "TestLayer.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

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

    std::shared_ptr<Texture> container = std::make_unique<Texture>("../Sandbox/assets/textures/container.jpg");
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
    std::shared_ptr<IndexBuffer> ibo = std::make_shared<IndexBuffer>(indices, 6);
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

void TestLayer::OnUpdate()
{
    Renderer::Clear();
    m_VertexArray->Bind();
    Renderer::Draw(m_VertexArray->GetIndexBuffer()->GetCount());
}
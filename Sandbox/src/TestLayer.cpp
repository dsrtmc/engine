#include "TestLayer.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

using namespace Engine;

TestLayer::TestLayer()
    // : Layer("Test layer")
{
    // ENG_TRACE("Created Test layer");
    std::cout << "destroyed test layer\n";
    // Texture container("../Sandbox/assets/textures/container.jpg");
    // container.Bind(0);

    // float vertices[] = {
    //     -0.5f, -0.5f, 0.0f, -1.0f, -1.0f,
    //      0.5f, -0.5f, 0.0f,  1.0f, -1.0f,
    //      0.5f,  0.5f, 0.0f,  1.0f,  1.0f,
    //     -0.5f,  0.5f, 0.0f, -1.0f,  1.0f
    // };

    // GLuint indices[] = {
    //     0, 1, 2,
    //     2, 3, 0
    // };

    // // Create a vertex array object
    // VertexArray vao;
    // vao.Bind();
    // m_VertexArray = &vao;

    // // Specify a layout of our vertices
    // BufferLayout layout;
    // // 3 coordinates per attribute => one Push() call == one attribute
    // layout.Push(3);
    // layout.Push(2);

    // // Create a vertex buffer object and bind it to the specified layout
    // VertexBuffer vbo(vertices, sizeof(vertices));
    // vbo.SetLayout(layout);

    // // Create an index buffer object 
    // IndexBuffer ibo(indices, 6);
    // ibo.Bind();

    // // Make the buffers the vertex array's private members, not used yet
    // vao.SetVertexBuffer(vbo);
    // vao.SetIndexBuffer(ibo);
}

TestLayer::~TestLayer()
{
    // ENG_TRACE("Destroyed Test layer");
    std::cout << "destroyed test layer\n";
}

void TestLayer::OnUpdate()
{
    // m_VertexArray->Bind();
    // // ibo.GetCount();
    // Renderer::Draw(36);
}

void TestLayer::OnImGuiRender()
{
    ImGui::Begin("Settings");
    ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
    ImGui::End();
}
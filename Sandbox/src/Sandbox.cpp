#include "Sandbox.h"
#include <string>

using namespace Engine;

void Sandbox::PollEvents()
{
    if (glfwGetKey(m_Window->GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        m_Running = false;
    }
}

Sandbox::Sandbox()
{
    m_Window = Window::Create();
}

Sandbox::~Sandbox()
{
    m_Window->Shutdown();
}

void Sandbox::Initialize()
{
    // m_Window->SetEventCallback((EventCallbackFn)&Sandbox::EventCallback);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        ENG_ERROR("Failed to initialize GLAD");
    }

    std::string version = std::string((const char *)glGetString(GL_VERSION));
    ENG_INFO("OpenGL version: {0}", version);
}

// Main app logic
void Sandbox::Run()
{
    Initialize();

    // Filepaths are relative from /build/
    m_Shader = std::unique_ptr<Shader>(Shader::FromTextFiles(
        "../Sandbox/assets/shaders/shader.vert.glsl",
        "../Sandbox/assets/shaders/shader.frag.glsl"
    ));
    m_Shader->Bind();

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };

    GLuint indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    // Create a vertex array object
    VertexArray vao;
    vao.Bind();

    // Specify a layout of our vertices
    BufferLayout layout;
    // 3 coordinates per attribute => one Push() call == one attribute
    layout.Push(3);

    // Create a vertex buffer object and bind it to the specified layout
    VertexBuffer vbo(vertices, sizeof(vertices));
    vbo.SetLayout(layout);

    // Create an index buffer object 
    IndexBuffer ibo(indices, 6);
    ibo.Bind();

    // Make the buffers the vertex array's private members, not used yet
    vao.SetVertexBuffer(vbo);
    vao.SetIndexBuffer(ibo);

    // Main app loop
    while (m_Running)
    {
        PollEvents();
        Renderer::Clear();
        glClearColor(0.075f, 0.075f, 0.075f, 1.0f);

        vao.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        m_Window->OnUpdate();
    }
}
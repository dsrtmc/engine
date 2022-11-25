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

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    VertexBuffer vbo(vertices, sizeof(vertices));
    vbo.Bind();

    IndexBuffer ibo(indices, 6);
    ibo.Bind();

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (const void *)0);
    glEnableVertexAttribArray(0);

    while (m_Running)
    {
        PollEvents();
        Renderer::Clear();
        glClearColor(0.075f, 0.075f, 0.075f, 1.0f);
        // glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        m_Window->OnUpdate();
    }
}
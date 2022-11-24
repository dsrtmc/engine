#include "Sandbox.h"
#include <string>

using namespace Engine;

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
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        ENG_ERROR("Failed to initialize GLAD");
    }

    std::string version = std::string((const char *)glGetString(GL_VERSION));
    ENG_INFO("OpenGL version: {0}", version);
}

void Sandbox::ProcessInput()
{
    if (glfwGetKey(m_Window->GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        m_Running = false;
    }
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
         -0.5f, 0.5f, 0.0f
    };

    GLuint indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (const void *)0);
    glEnableVertexAttribArray(0);

    while (m_Running)
    {
        ProcessInput();
        glClearColor(0.075f, 0.075f, 0.075f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        m_Window->OnUpdate();
    }
}
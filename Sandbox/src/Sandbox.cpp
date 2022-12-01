#include "Sandbox.h"
#include <string>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

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

    Texture container("../Sandbox/assets/textures/container.jpg");
    container.Bind(0);

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
    VertexArray vao;
    vao.Bind();

    // Specify a layout of our vertices
    BufferLayout layout;
    // 3 coordinates per attribute => one Push() call == one attribute
    layout.Push(3);
    layout.Push(2);

    // Create a vertex buffer object and bind it to the specified layout
    VertexBuffer vbo(vertices, sizeof(vertices));
    vbo.SetLayout(layout);

    // Create an index buffer object 
    IndexBuffer ibo(indices, 6);
    ibo.Bind();

    // Make the buffers the vertex array's private members, not used yet
    vao.SetVertexBuffer(vbo);
    vao.SetIndexBuffer(ibo);

    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(m_Window->GetWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330");
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    // Main app loop
    while (m_Running)
    {
        PollEvents();
        Renderer::Clear();
        glClearColor(0.075f, 0.075f, 0.075f, 1.0f);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
        ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
        ImGui::End();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        vao.Bind();
        Renderer::Draw(ibo.GetCount());
        m_Window->OnUpdate();
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
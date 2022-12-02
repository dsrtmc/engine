#include "Sandbox.h"

// #include "Test2D.h"
// #include "TestLayer.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

using namespace Engine;

Sandbox::Sandbox()
{
    ENG_INFO("Created a sandbox");
    m_Window = Window::Create({ "Engine", 1440, 900 });
    // generally we should have a function PushLayer() that also calls layer's OnAttach()
    UILayer *ui = new UILayer;
    m_Layers.push_back(ui);
}

Sandbox::~Sandbox()
{
    m_Window->Shutdown();
    for (auto *layer : m_Layers)
    {
        delete layer;
    }
}

void Sandbox::Initialize()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        ENG_ERROR("Failed to initialize GLAD");
    }

    std::string version = std::string((const char *)glGetString(GL_VERSION));
    ENG_INFO("OpenGL version: {0}", version);
}

void Sandbox::PollEvents()
{
    if (glfwGetKey(m_Window->GetGLFWwindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        m_Running = false;
    }
}

// Main app logic
void Sandbox::Run()
{
    Initialize();
    // Filepaths are relative from /build/
    m_Shader = std::unique_ptr<Shader>(Shader::FromTextFiles( "../Sandbox/assets/shaders/shader.vert.glsl",
        "../Sandbox/assets/shaders/shader.frag.glsl"
    ));
    m_Shader->Bind();

    Texture container("../Sandbox/assets/textures/container.jpg");
    container.Bind(0);
    
    // TestLayer testlayer;

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
    ImGui_ImplGlfw_InitForOpenGL(m_Window->GetGLFWwindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330");
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    int counter = 0;
    float f = 0.0f;
    // Main app loop
    while (m_Running)
    {
        PollEvents();
        Renderer::Clear();
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
        ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
        ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
        ImGui::Checkbox("Another Window", &show_another_window);

        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::ColorEdit3("clear color", (float *)&clear_color); // Edit 3 floats representing a color

        if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();

        vao.Bind();
        Renderer::Draw(ibo.GetCount());
        // testlayer.OnUpdate();
        // testlayer.OnImGuiRender();

        for (auto *layer : m_Layers)
        {
            layer->OnUpdate();
        }

        m_Window->OnUpdate();
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
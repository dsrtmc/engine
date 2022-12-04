#include "Sandbox.h"

// #include "Test2D.h"
#include "TestLayer.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

using namespace Engine;

Sandbox::Sandbox()
{
    ENG_INFO("Created sandbox");
    m_Window = Window::Create({ "Engine", 1440, 900 });
    // Ideally, we should have a function like PushLayer() that also calls layer's OnAttach()
    // UILayer Takes care of rendering all ImGui elements
    UILayer *ui = new UILayer;
    m_Layers.push_back(ui);
}

Sandbox::~Sandbox()
{
    m_Window->Shutdown();

    // Ideally do that inside a LayerStack
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
    TestLayer mainLayer;

    // TODO: Move that to UILayer class, can't do that now because
    // we don't have accesss to Window inside that class
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(m_Window->GetGLFWwindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330");

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    int counter = 0;
    float f = 0.0f;
    // Main app loop
    while (m_Running)
    {
        PollEvents();
        Renderer::Clear();
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);

        // Write ImGui code below that
        mainLayer.OnImGuiRender();

        ImGui::Begin("Hello, world!");                               // Create a window called "Hello, world!" and append into it.
            ImGui::Text("This is some useful text.");                // Display some text (you can use a format strings too)
            ImGui::ColorEdit3("clear color", (float *)&clear_color); // Edit 3 floats representing a color
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();

        mainLayer.OnUpdate();

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
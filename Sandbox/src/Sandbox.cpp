#include "Sandbox.h"

// #include "Test2D.h"
#include "TestLayer.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

using namespace Engine;

Sandbox::Sandbox()
{
    // Create a window and initialize GLAD
    m_Window = Window::Create({ "Engine", 1440, 900 });
    Initialize();

    m_UILayer = std::make_unique<UILayer>();

    // Ideally, we should have a function like PushLayer() that also calls layer's OnAttach()
    TestLayer *testLayer = new TestLayer;
    m_Layers.push_back(testLayer);

    ENG_INFO("Created sandbox");
}

Sandbox::~Sandbox()
{
    m_Window->Shutdown();

    // Ideally do that inside a LayerStack
    for (Layer *layer : m_Layers)
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
    if (glfwGetKey(m_Window->GetNativeWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        m_Running = false;
    }
}

// Main app logic
void Sandbox::Run()
{
    // TODO: Move that to UILayer class, can't do that now because
    // we don't have accesss to Window inside that class
    ImGui_ImplGlfw_InitForOpenGL(m_Window->GetNativeWindow(), true);

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    // Main app loop
    while (m_Running)
    {
        PollEvents();
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);

        for (Layer *layer : m_Layers)
        {
            layer->OnUpdate();
        }

        // Write ImGui inbetween Begin() and End() tags
        m_UILayer->Begin();
        ImGui::Begin("Hello, world!");                               // Create a window called "Hello, world!" and append into it.
            ImGui::Text("This is some useful text.");                // Display some text (you can use a format strings too)
            ImGui::ColorEdit3("clear color", (float *)&clear_color); // Edit 3 floats representing a color
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
        m_UILayer->End();

        m_Window->OnUpdate();
    }
}
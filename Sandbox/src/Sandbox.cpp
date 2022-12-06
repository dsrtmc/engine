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
    m_Layers.push_back(new TestLayer);

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

    // Main app loop
    while (m_Running)
    {
        PollEvents();
        glClearColor(0.07f, 0.07f, 0.07f, 1.0f);

        for (Layer *layer : m_Layers)
        {
            layer->OnUpdate();
        }

        m_UILayer->Begin();
        for (Layer *layer : m_Layers)
        {
            layer->OnImGuiUpdate();
        }
        m_UILayer->End();

        m_Window->OnUpdate();
    }
}
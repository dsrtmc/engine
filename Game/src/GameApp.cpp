#include "GameApp.h"

#include "GameLayer.h"

using namespace Engine;

GameApp::GameApp()
{
    // Required to make this the main application instance
    s_Instance = this;

    // Create a window, set its event callbacks
    m_Window = Window::Create({ "Engine", 1440, 900 }); // The only reason why I call it engine is so that it works better with my tiling WM

    // The window's event callback now becomes Sandbox's OnEvent() function
    m_Window->SetEventCallback([&](Event &e){ return OnEvent(e); });

    // Initialize GLAD, log OpenGL version
    Initialize();

    m_UILayer = std::make_unique<UILayer>();

    // Ideally, we should have a function like PushLayer() that also calls layer's OnAttach()
    m_Layers.push_back(new GameLayer);

    ENG_INFO("Created Sandbox");
}

GameApp::~GameApp()
{
    // Ideally do that for a LayerStack
    for (Layer *layer : m_Layers)
        delete layer;

    delete m_Window;
    ENG_INFO("Destroyed Sandbox");
}

// App's event callback
void GameApp::OnEvent(Event &event)
{
    for (Layer *layer : m_Layers)
        layer->OnEvent(event);

    // Write app-specific events below
    EventType type = event.GetType();
    if (type == EventType::WindowClosed)
        m_Running = false;

    if (type == EventType::KeyPressed)
    {
        if (Input::IsKeyPressed(ENG_KEY_ESCAPE))
            m_Running = false;
    }

    // Update the viewport on window resize
    if (type == EventType::WindowResized)
    {
        int width, height;
        glfwGetFramebufferSize(m_Window->GetNativeWindow(), &width, &height);
        glViewport(0, 0, width, height);
    }
}

// Initialize GLAD, log OpenGL version
void GameApp::Initialize()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        ENG_ERROR("Failed to initialize GLAD");

    std::string version = std::string((const char *)glGetString(GL_VERSION));
    ENG_INFO("OpenGL version: {0}", version);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);

    // TODO: make engine specific not app specific i guess?
    // Set up logging for OpenGL debug messages
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback([](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
    {
        switch (severity)
        {
            case GL_DEBUG_SEVERITY_NOTIFICATION:
                // ENG_TRACE("OpenGL notification ({0}): {1}", id, message);
                break;
            case GL_DEBUG_SEVERITY_LOW:
                ENG_INFO("(OpenGL) info {0}: {1}", id, message);
                break;
            case GL_DEBUG_SEVERITY_MEDIUM:
                ENG_WARN("(OpenGL) warning {0}: {1}", id, message);
                break;
            case GL_DEBUG_SEVERITY_HIGH:
                ENG_ERROR("(OpenGL) error {0}: {1}", id, message);
                break;
        }
    }, nullptr);
}

// Main app logic
void GameApp::Run()
{
    while (m_Running)
    {
        // Calculate the timestep for OnUpdate() methods
        float time = glfwGetTime();
        float timestep = time - m_LastFrameTime;
        m_LastFrameTime = time;

        for (Layer *layer : m_Layers)
            layer->OnUpdate(timestep);

        m_UILayer->Begin();
        for (Layer *layer : m_Layers)
            layer->OnImGuiUpdate();
        m_UILayer->End();

        m_Window->OnUpdate();
    }
}

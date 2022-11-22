#include "Sandbox.h"

Sandbox::Sandbox()
{
    m_Window = Engine::Window::Create();
}

Sandbox::~Sandbox()
{
    m_Window->Shutdown();
}

// Main app logic
void Sandbox::Run()
{
    ENG_INFO("Started the sandbox");
    while (m_Running)
    {
        glClearColor(1.0f, 0.2f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        m_Window->OnUpdate();
    }
}
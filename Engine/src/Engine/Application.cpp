#include "Application.h"
#include "Log.h"

#include <iostream>

namespace Engine
{

    Application::Application()
    {
        m_Window = Window::Create();
    };

    Application::~Application()
    {
        delete m_Window;
    };

    void Application::Run()
    {
        while (m_Running)
        {
            m_Window->OnUpdate();
        }
    }
};